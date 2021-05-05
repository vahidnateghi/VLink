#include "VLink_Pack.h"

int VLink_Pack::m_IdCounter = 0;

VLink_Pack::VLink_Pack(QObject *parent) : QObject(parent)
{
    m_ID = m_IdCounter++;
}
