#include "VLink.h"

int VLink::m_IdCounter = 0;

VLink::VLink(QObject *parent) : QObject(parent)
{
    m_ID = m_IdCounter++;
}

int VLink::ID() const
{
    return m_ID;
}
