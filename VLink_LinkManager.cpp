#include "VLink_LinkManager.h"
#include <Link/UDP_VLink.h>

VLink_LinkManager::VLink_LinkManager(QObject *parent) : QObject(parent)
{

}

void VLink_LinkManager::setBuffer(const ShrdPtrBuffer &Buffer)
{
    m_Buffer = Buffer;
}

void VLink_LinkManager::AddLink(LinkType type, ShrdPtrInfo Info)
{
    QThread* tThread = new QThread();
    switch (type) {
    case Link_UDP:
        ShrdPtrLink newLink = ShrdPtrLink( new UDP_VLink() );
        connect( this, &VLink_LinkManager::SgSendBytes, [newLink](const QByteArray& Bytes)
        {
           newLink.data()->SendBytes( Bytes );
        });
        connect( newLink.data(), &VLink::SgNewInput, this, &VLink_LinkManager::SltPrNewBytes );
        connect( this, &VLink_LinkManager::SgInit, newLink.data(), &VLink::InitLink );

        newLink.data()->moveToThread( tThread );
        tThread->start( QThread::HighestPriority );
        m_Links.append( newLink );
        m_Threads.append( tThread );
        emit SgInit( Info );
        break;
    }
}

void VLink_LinkManager::SendBytes(const QByteArray &Bytes)
{
    emit SgSendBytes( Bytes );
}

void VLink_LinkManager::SltPrNewBytes(ShrdPtrByteArray bytes)
{
    if( m_Buffer.data() == NULL )
        return;


    m_Buffer.data()->insert( m_Buffer.data()->end(), bytes.data()->begin(), bytes.data()->end() );
}
