#ifndef SERIAL_VLINK_H
#define SERIAL_VLINK_H

#include <QObject>
#include <VLink_Infos/Serial_Info.h>
#include <VLink_Links/VLink.h>
#include <QSerialPort>

class Serial_VLink : public VLink
{
    Q_OBJECT
public:
    explicit Serial_VLink(QObject *parent = nullptr);


public slots:
    int SendBytes(const QByteArray &Bytes);
    void Start();
    void FinLink();

private:
    QSerialPort *m_Port;
};

#endif // SERIAL_VLINK_H
