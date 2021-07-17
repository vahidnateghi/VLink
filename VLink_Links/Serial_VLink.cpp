#include "Serial_VLink.h"

Serial_VLink::Serial_VLink(QObject *parent) : VLink(parent)
{
    m_Port = new QSerialPort( this );
    connect( m_Port, &QSerialPort::readyRead, [this]()
    {
        int rsize = m_Port->bytesAvailable();
        ShrdPtrByteArray rBytes = ShrdPtrByteArray( new QByteArray() );
        rBytes.data()->resize( rsize );
        m_Port->read( rBytes.data()->data(), rsize );

        emit SgNewInput( rBytes );
    });
}

void Serial_VLink::FinLink()
{
    if( !m_IsInitialized )
        return;
    m_IsInitialized = false;

    if( m_Port->isOpen() )
    {
        m_Port->close();
    }
    emit SgStopped();
}

int Serial_VLink::SendBytes(const QByteArray &Bytes)
{
    if( !m_IsInitialized )
        return 0;

    m_Port->write( Bytes );
    m_Port->flush();
}

void Serial_VLink::Start()
{
    if( m_LinkInfo.data() == NULL )
        return;

    if( m_IsInitialized )
        return;


    Serial_Info* info = (Serial_Info*)m_LinkInfo.data();
    m_Port->setPortName( info->PortName() );
    m_Port->setBaudRate( info->BaudRate() );
    m_Port->setStopBits( QSerialPort::StopBits::OneStop );
    m_Port->setParity( QSerialPort::Parity::NoParity );
    m_Port->setDataBits( QSerialPort::DataBits::Data8 );
    if( m_Port->open( QIODevice::ReadWrite ) )
    {
        m_IsInitialized = true;
        m_Port->readAll();

        emit SgStarted();
    }


}
