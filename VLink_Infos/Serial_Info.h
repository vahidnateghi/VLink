#ifndef SERIAL_INFO_H
#define SERIAL_INFO_H

#include "LinkInfo.h"
#include <QSerialPort>

class Serial_Info : public LinkInfo
{
    Q_OBJECT
public:
    explicit Serial_Info(QObject *parent = nullptr);

    int BaudRate() const;
    void setBaudRate(int BaudRate);

    QString PortName() const;
    void setPortName(const QString &PortName);

    QSerialPort::StopBits StopBit() const;
    void setStopBit(QSerialPort::StopBits StopBit);

    QSerialPort::DataBits DataBits() const;
    void setDataBits(QSerialPort::DataBits DataBits);

    QSerialPort::Parity Parity() const;
    void setParity(const QSerialPort::Parity &Parity);

private:
    int m_BaudRate;
    QString m_PortName;
    QSerialPort::StopBits m_StopBit;
    QSerialPort::DataBits m_DataBits;
    QSerialPort::Parity m_Parity;

};

#endif // SERIAL_INFO_H
