#include "VLink_LinkManager.h"
#include <VLink_Links/UDP_VLink.h>
#include <VLink_Links/Serial_VLink.h>
#include <iostream>

VLink_LinkManager::VLink_LinkManager(QObject *parent) : QObject(parent)
{

}

int VLink_LinkManager::AddLink(LinkType type, ShrdPtrInfo Info)
{
    QThread* tThread = new QThread();
    if( type == Link_UDP )
    {
        ShrdPtrLink newLink = ShrdPtrLink( new UDP_VLink() );
        connect( this, &VLink_LinkManager::SgSendBytes, newLink.data(), &VLink::SendBytes );
        connect( newLink.data(), &VLink::SgNewInput, this, &VLink_LinkManager::SltPrNewBytes );
        connect( newLink.data(), &VLink::SgStarted, [this,newLink]()
        {
            emit SgStarted( newLink.data()->ID() );
        });
        connect( newLink.data(), &VLink::SgStopped, [this,newLink]()
        {
            emit SgStopped( newLink.data()->ID() );
        });
        connect( this, &VLink_LinkManager::SgStart, newLink.data(), &VLink::Start );
        connect( this, &VLink_LinkManager::SgStop, newLink.data(), &VLink::FinLink );

        newLink.data()->InitLink( Info );

        newLink.data()->moveToThread( tThread );
        tThread->start( QThread::HighestPriority );
        m_Links.append( newLink );
        m_Threads.append( tThread );
        return newLink.data()->ID();
    }
    else if( type == Link_Serial )
    {
        ShrdPtrLink serLink = ShrdPtrLink( new Serial_VLink() );
        connect( this, &VLink_LinkManager::SgSendBytes, serLink.data(), &VLink::SendBytes );
        connect( serLink.data(), &VLink::SgNewInput, this, &VLink_LinkManager::SltPrNewBytes );
        connect( this, &VLink_LinkManager::SgStart, serLink.data(), &VLink::Start );
        connect( this, &VLink_LinkManager::SgStop, serLink.data(), &VLink::FinLink );
        connect( serLink.data(), &VLink::SgStarted, [this,serLink]()
        {
            emit SgStarted( serLink.data()->ID() );
        });
        connect( serLink.data(), &VLink::SgStopped, [this,serLink]()
        {
            emit SgStopped( serLink.data()->ID() );
        });

        serLink.data()->InitLink( Info );

        serLink.data()->moveToThread( tThread );
        tThread->start( QThread::HighestPriority );
        m_Links.append( serLink );
        m_Threads.append( tThread );
        return serLink.data()->ID();
    }

    return -1;
}

void VLink_LinkManager::SendBytes(const QByteArray &Bytes)
{
    Q_FOREACH(ShrdPtrLink link, m_Links)
    {
        link.data()->SendBytes( Bytes );
    }
}

void VLink_LinkManager::SendBytes(ShrdPtrByteArray Bytes)
{
    Q_FOREACH(ShrdPtrLink link, m_Links)
    {
        QByteArray tBytes(*Bytes.data());
        link.data()->SendBytes( tBytes );
    }
}

void VLink_LinkManager::setBufferMutex(const ShrdPtrMutex &BufferMutex)
{
    m_BufferMutex = BufferMutex;
}

void VLink_LinkManager::Start()
{
    emit SgStart();
}

void VLink_LinkManager::Stop()
{
    emit SgStop();
}

bool VLink_LinkManager::IsInitialized()
{
    bool Init = true;
    foreach (ShrdPtrLink Link, m_Links) {
        if( !Link.data()->IsInitialized() )
            Init = false;
    }

    return Init;
}

ShrdPtrInfo VLink_LinkManager::LinkInfo(int LinkID)
{
    foreach (ShrdPtrLink Link, m_Links) {
        if( Link.data()->ID() == LinkID )
            return Link.data()->LinkInfo();

    }
}

void VLink_LinkManager::SltPrNewBytes(ShrdPtrByteArray bytes)
{
    emit SgNewBytes( bytes );
}
