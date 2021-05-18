#include "Serial_Info.h"

Serial_Info::Serial_Info(QObject *parent) : LinkInfo(parent)
{

}

int Serial_Info::BaudRate() const
{
    return m_BaudRate;
}

void Serial_Info::setBaudRate(int BaudRate)
{
    m_BaudRate = BaudRate;
}

QString Serial_Info::PortName() const
{
    return m_PortName;
}

void Serial_Info::setPortName(const QString &PortName)
{
    m_PortName = PortName;
}

QSerialPort::StopBits Serial_Info::StopBit() const
{
    return m_StopBit;
}

void Serial_Info::setStopBit(QSerialPort::StopBits StopBit)
{
    m_StopBit = StopBit;
}

QSerialPort::DataBits Serial_Info::DataBits() const
{
    return m_DataBits;
}

void Serial_Info::setDataBits(QSerialPort::DataBits DataBits)
{
    m_DataBits = DataBits;
}

QSerialPort::Parity Serial_Info::Parity() const
{
    return m_Parity;
}

void Serial_Info::setParity(const QSerialPort::Parity &Parity)
{
    m_Parity = Parity;
}
