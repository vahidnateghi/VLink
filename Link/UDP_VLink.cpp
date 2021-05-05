#include "UDP_VLink.h"
#include <QSharedPointer>

UDP_VLink::UDP_VLink(QObject *parent) : VLink(parent)
{
    m_IsInitialized = false;
    m_Socket = NULL;
    m_IsReading = false;
}

void UDP_VLink::InitLink(ShrdPtrInfo Info)
{
    if( m_IsInitialized )
        return;

    m_LinkInfo = Info;
    UDP_Info* tInfo = (UDP_Info*)m_LinkInfo.data();

    m_Socket = new QUdpSocket();
    m_Socket->bind( QHostAddress(tInfo->m_PeerIP), tInfo->m_RxPort );

    m_IsInitialized = true;
    m_IsReading = true;

    while( m_IsReading )
    {
        int rsize = m_Socket->bytesAvailable();
        if( rsize < 1 )
            continue;

        ShrdPtrByteArray rBytes = ShrdPtrByteArray( new QByteArray() );
        rBytes.data()->resize( rsize );
        m_Socket->readDatagram( rBytes.data()->data(), rsize );

        emit SgNewInput( rBytes );
    }
}

int UDP_VLink::SendBytes(const QByteArray &Bytes)
{
    if( !m_IsInitialized )
        return 0;

    UDP_Info* tInfo = (UDP_Info*)m_LinkInfo.data();

    int ssize = m_Socket->writeDatagram( Bytes, QHostAddress( tInfo->m_PeerIP ), tInfo->m_TxPort );
    return ssize;
}

void UDP_VLink::FinLink()
{
    if( !m_IsInitialized )
        return;

    m_IsReading = false;
    m_IsInitialized = false;
}
