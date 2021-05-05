#ifndef UDP_INFO_H
#define UDP_INFO_H

#include "LinkInfo.h"

class UDP_Info : public LinkInfo
{
    Q_OBJECT
public:
    explicit UDP_Info(QObject *parent = nullptr);
    void operator =(const UDP_Info &newInfo);

    int m_RxPort;
    int m_TxPort;
    QString m_PeerIP;

};

#endif // UDP_INFO_H
