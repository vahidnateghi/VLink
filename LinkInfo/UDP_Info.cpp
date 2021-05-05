#include "UDP_Info.h"

UDP_Info::UDP_Info(QObject *parent) : LinkInfo(parent)
{
    m_RxPort = 4000;
    m_TxPort = 4001;
    m_PeerIP = "127.0.0.1";
}

void UDP_Info::operator=(const UDP_Info &newInfo)
{
    m_RxPort = newInfo.m_RxPort;
    m_TxPort = newInfo.m_TxPort;
    m_PeerIP = newInfo.m_PeerIP;
}
