#ifndef UDP_VLINK_H
#define UDP_VLINK_H

#include "VLink.h"
#include "LinkInfo/UDP_Info.h"
#include <QUdpSocket>

class UDP_VLink : public VLink
{
    Q_OBJECT
public:
    explicit UDP_VLink(QObject *parent = nullptr);

    int SendBytes(const QByteArray &Bytes);
    void FinLink();

public slots:
    void InitLink( ShrdPtrInfo Info);

private:
    bool m_IsInitialized;
    QUdpSocket* m_Socket;
    bool m_IsReading;
};

#endif // UDP_VLINK_H
