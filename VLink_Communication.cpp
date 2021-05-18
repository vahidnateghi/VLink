#include "VLink_Communication.h"

int VLink_Communication::m_IdCounter = 0;

VLink_Communication::VLink_Communication(QObject *parent) : QObject(parent)
{
    m_ID = m_IdCounter++;

    m_SendNewBytesSignal = false;

    m_BufferMutex = ShrdPtrMutex(new QMutex());

    m_LinkManager.setBufferMutex( m_BufferMutex );
    m_PackManager.setBufferMutex( m_BufferMutex );

    m_PackMngrThread = new QThread();
    m_PackManager.moveToThread( m_PackMngrThread );
    m_PackMngrThread->start( QThread::HighestPriority );

    connect( this, &VLink_Communication::SgStart, &m_PackManager, &VLink_PackManager::SltPuAnaLoop );
    connect( &m_LinkManager, &VLink_LinkManager::SgNewBytes, &m_PackManager, &VLink_PackManager::SltPuNewBytes );
    connect( &m_LinkManager, &VLink_LinkManager::SgNewBytes, [this](ShrdPtrByteArray Bytes)
    {
        if( m_SendNewBytesSignal )
            emit SgNewBytes( Bytes );
    });
    connect( &m_LinkManager, &VLink_LinkManager::SgStarted, [this](int ID)
    {
        emit SgLinkStarted( ID );
    });
    connect( &m_LinkManager, &VLink_LinkManager::SgStopped, [this](int ID)
    {
        emit SgLinkStopped( ID );
    });

    connect( &m_PackManager, &VLink_PackManager::SgNewPack, [this](ShrdPtrPack pack)
    {
        emit SgNewPack( pack );
    });

    emit SgStart();
}

int VLink_Communication::AddLink(LinkType Type, ShrdPtrInfo Info)
{
    return m_LinkManager.AddLink( Type, Info );
}

void VLink_Communication::SendPack(VLink_Pack &pack)
{
    QByteArray sArray = pack.GetBytes();
    m_LinkManager.SendBytes( sArray );
}

void VLink_Communication::SendBytes(ShrdPtrByteArray sArray)
{
    m_LinkManager.SendBytes( sArray );
}

int VLink_Communication::ID() const
{
    return m_ID;
}

bool VLink_Communication::SendNewBytesSignal() const
{
    return m_SendNewBytesSignal;
}

void VLink_Communication::setSendNewBytesSignal(bool SendNewBytesSignal)
{
    m_SendNewBytesSignal = SendNewBytesSignal;
}

void VLink_Communication::Start()
{
    m_LinkManager.Start();
}

void VLink_Communication::Stop()
{
    m_LinkManager.Stop();
}

bool VLink_Communication::IsInitialized()
{
    return m_LinkManager.IsInitialized();
}

ShrdPtrInfo VLink_Communication::LinkInfo(int LinkID)
{
    return m_LinkManager.LinkInfo( LinkID );
}
