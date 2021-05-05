#include "VLink_Communication.h"

int VLink_Communication::m_IdCounter = 0;

VLink_Communication::VLink_Communication(QObject *parent) : QObject(parent)
{
    m_ID = m_IdCounter++;

    m_Buffer = ShrdPtrBuffer(new std::vector<char>());

    m_LinkManager.setBuffer( m_Buffer );
    m_PackManager.setBuffer( m_Buffer );

    m_PackMngrThread = new QThread();
    m_PackManager.moveToThread( m_PackMngrThread );
    m_PackMngrThread->start( QThread::HighestPriority );

    connect( this, &VLink_Communication::SgStart, &m_PackManager, &VLink_PackManager::SltPuAnaLoop );

    connect( &m_PackManager, &VLink_PackManager::SgNewPack, [this](ShrdPtrPack pack)
    {
        emit SgNewPack( pack );
    });

    emit SgStart();
}

void VLink_Communication::AddLink(LinkType Type, ShrdPtrInfo Info)
{
    m_LinkManager.AddLink( Type, Info );
}

void VLink_Communication::SendPack(VLink_Pack &pack)
{
    QByteArray sArray = pack.GetBytes();
    m_LinkManager.SendBytes( sArray );
}

int VLink_Communication::ID() const
{
    return m_ID;
}
