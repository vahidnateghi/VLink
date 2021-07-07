#include "UDP_VLink.h"
#include <QSharedPointer>
#include <iostream>
#include <QDebug>

UDP_VLink::UDP_VLink(QObject *parent) : VLink(parent)
{
    m_Socket = NULL;
    m_IsReading = false;

    m_Socket = new QUdpSocket( this );
    m_Socket->setSocketOption( QAbstractSocket::KeepAliveOption, 1 );

    connect( m_Socket, &QUdpSocket::readyRead, [this]()
    {
//        std::cout << "===========" << std::endl;
//        if( m_StopWatch.isValid() )
//            m_StopWatch.restart();
//        else
//            m_StopWatch.start();

        int rsize = m_Socket->pendingDatagramSize();
        ShrdPtrByteArray rBytes = ShrdPtrByteArray( new QByteArray() );
        rBytes.data()->resize( rsize );
        m_Socket->readDatagram( rBytes.data()->data(), rsize );

//        std::cout << "Read Datagram Time: " << m_StopWatch.nsecsElapsed() << std::endl;
//        m_StopWatch.restart();

        emit SgNewInput( rBytes );
    } );
}

int UDP_VLink::SendBytes(const QByteArray &Bytes)
{
    if( !m_IsInitialized )
        return 0;

//    qint64 purProcessTime = m_StopWatch.nsecsElapsed();
//    m_StopWatch.restart();

    UDP_Info* tInfo = (UDP_Info*)m_LinkInfo.data() ;

    int ssize = m_Socket->writeDatagram( Bytes, QHostAddress( tInfo->m_PeerIP ), tInfo->m_TxPort );
    m_Socket->flush();
//    std::cout << "Pure Process Time : " << purProcessTime << std::endl;
//    std::cout << "UDP Send Time : " << m_StopWatch.nsecsElapsed() << std::endl;
//    qDebug() << "Sent " << ssize << " Bytes!";
    return ssize;
}

void UDP_VLink::Start()
{
    if( m_LinkInfo.data() == NULL )
        return;

    UDP_Info* tInfo = (UDP_Info*)m_LinkInfo.data();


    if( !m_Socket->bind( tInfo->m_RxPort ) )
    {
        std::cout << "UDP Socket not bound!" << std::endl;
        return;
    }

    m_Socket->flush();

    m_IsInitialized = true;
    m_IsReading = true;

    emit SgStarted();
}

void UDP_VLink::FinLink()
{
    if( !m_IsInitialized )
        return;

    m_IsReading = false;
    m_IsInitialized = false;
    if( m_Socket->BoundState )
        m_Socket->close();

    emit SgStopped();
}
