#include "VLink.h"

int VLink::m_IdCounter = 0;

VLink::VLink(QObject *parent) : QObject(parent)
{
    m_ID = m_IdCounter++;
    m_LinkInfo = ShrdPtrInfo(NULL);
    m_IsInitialized = false;
}

int VLink::ID() const
{
    return m_ID;
}

ShrdPtrInfo VLink::LinkInfo() const
{
    return m_LinkInfo;
}

void VLink::setLinkInfo(const ShrdPtrInfo &LinkInfo)
{
    m_LinkInfo = LinkInfo;
}

bool VLink::IsInitialized() const
{
    return m_IsInitialized;
}

void VLink::InitLink(ShrdPtrInfo info)
{
    if( m_IsInitialized )
        return;

    m_LinkInfo = info;
}
