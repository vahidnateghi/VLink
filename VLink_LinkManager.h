#ifndef VLINK_LINKMANAGER_H
#define VLINK_LINKMANAGER_H

#include <QObject>
#include <VLink_Defines.h>
#include <Link/VLink.h>
#include <LinkInfo/LinkInfo.h>
#include <LinkInfo/UDP_Info.h>
#include <QThread>

class VLink_LinkManager : public QObject
{
    Q_OBJECT
public:
    explicit VLink_LinkManager(QObject *parent = nullptr);

    void setBuffer(const ShrdPtrBuffer &Buffer);
    void AddLink(LinkType type, ShrdPtrInfo Info );
    void SendBytes( const QByteArray& Bytes );

private:
    ShrdPtrBuffer m_Buffer;
    QList<ShrdPtrLink> m_Links;
    QList<QThread*> m_Threads;

private slots:
    void SltPrNewBytes(ShrdPtrByteArray bytes);

signals:
    void SgSendBytes( const QByteArray& );
    void SgInit( ShrdPtrInfo );
};

#endif // VLINK_LINKMANAGER_H
