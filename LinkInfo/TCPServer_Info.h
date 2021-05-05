#ifndef TCPSERVER_INFO_H
#define TCPSERVER_INFO_H

#include "LinkInfo.h"

class TCPServer_Info : public LinkInfo
{
    Q_OBJECT
public:
    explicit TCPServer_Info(QObject *parent = nullptr);
    void operator =(const TCPServer_Info &newInfo);

    int m_Port;

};

#endif // TCPSERVER_INFO_H
