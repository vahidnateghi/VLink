#ifndef UDP_VLINK_H
#define UDP_VLINK_H

#include "VLink.h"
#include "VLink_Infos/UDP_Info.h"
#include <QUdpSocket>

class UDP_VLink : public VLink
{
    Q_OBJECT
public:
    explicit UDP_VLink(QObject *parent = nullptr);


public slots:
    int SendBytes(const QByteArray &Bytes);
    void Start();
    void FinLink();

private:
    QUdpSocket* m_Socket;
    bool m_IsReading;

};

#endif // UDP_VLINK_H
