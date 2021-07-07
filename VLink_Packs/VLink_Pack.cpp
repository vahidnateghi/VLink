#include "VLink_Pack.h"

int VLink_Pack::m_IdCounter = 0;

VLink_Pack::VLink_Pack(QObject *parent) : QObject(parent)
{
    m_ID = m_IdCounter++;
}

VLink_Pack::VLink_Pack(const VLink_Pack &newLink)
{
    m_ID = newLink.m_ID;
}
