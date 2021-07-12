#ifndef VLINK_LINKMANAGER_H
#define VLINK_LINKMANAGER_H

#include <QObject>
#include <VLink_Defines.h>
#include <VLink_Links/VLink.h>
#include <VLink_Infos/LinkInfo.h>
#include <VLink_Infos/UDP_Info.h>
#include <QThread>
#include <QMutex>

class VLink_LinkManager : public QObject
{
    Q_OBJECT
public:
    explicit VLink_LinkManager(QObject *parent = nullptr);

    int AddLink(LinkType type, ShrdPtrInfo Info );
    void SendBytes( const QByteArray& Bytes );
    void SendBytes( ShrdPtrByteArray Bytes );
    void setBufferMutex(const ShrdPtrMutex &BufferMutex);
    void Start();
    void Stop();
    bool IsInitialized();

    ShrdPtrInfo LinkInfo( int LinkID );
    ShrdPtrLink Link( int LinkID );

private:
    QList<ShrdPtrLink> m_Links;
    QList<QThread*> m_Threads;
    ShrdPtrMutex m_BufferMutex;

private slots:
    void SltPrNewBytes(ShrdPtrByteArray bytes);

signals:
    void SgSendBytes( const QByteArray& );
    void SgNewBytes(ShrdPtrByteArray);
    void SgStart();
    void SgStarted(int ID);
    void SgStop();
    void SgStopped(int ID);
};

#endif // VLINK_LINKMANAGER_H
