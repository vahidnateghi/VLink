#ifndef TCPCLIENT_INFO_H
#define TCPCLIENT_INFO_H

#include "LinkInfo.h"

class TCPClient_Info : public LinkInfo
{
    Q_OBJECT
public:
    explicit TCPClient_Info(QObject *parent = nullptr);
    void operator =(const TCPClient_Info &newInfo);

    QString m_Host;
    int m_Port;

};

#endif // TCPCLIENT_INFO_H
