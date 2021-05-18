#include "TCPClient_Info.h"

TCPClient_Info::TCPClient_Info(QObject *parent) : LinkInfo(parent)
{

}

void TCPClient_Info::operator =(const TCPClient_Info &newInfo)
{
    m_Host = newInfo.m_Host;
    m_Port = newInfo.m_Port;
}
