#ifndef VLINK_COMMUNICATION_H
#define VLINK_COMMUNICATION_H

#include <QObject>
#include <VLink_LinkManager.h>
#include <VLink_PackManager.h>
#include <VLink_Defines.h>
#include <VLink_Packs/VLink_Pack.h>
#include <QThread>

class VLink_Communication : public QObject
{
    Q_OBJECT
public:
    explicit VLink_Communication(QObject *parent = nullptr);
    int AddLink(LinkType Type, ShrdPtrInfo Info);
    void SendPack(VLink_Pack &pack );
    void SendBytes(ShrdPtrByteArray sArray);
    template <class T>
    void AddPack()
    {
        m_PackManager.AddPack( ShrdPtrPack( new T() ) );
    }

    int ID() const;

    bool SendNewBytesSignal() const;
    void setSendNewBytesSignal(bool SendNewBytesSignal);

    void Start();
    void Stop();
    bool IsInitialized();
    ShrdPtrInfo LinkInfo( int LinkID );

private:
    static int m_IdCounter;
    VLink_LinkManager m_LinkManager;
    VLink_PackManager m_PackManager;
    ShrdPtrMutex m_BufferMutex;
    int m_ID;
    QThread* m_PackMngrThread;
    bool m_SendNewBytesSignal;


signals:
    void SgNewPack(ShrdPtrPack);
    void SgNewBytes(ShrdPtrByteArray);
    void SgStart();
    void SgLinkStarted(int);
    void SgLinkStopped(int);
};

typedef QSharedPointer<VLink_Communication> ShrdPtrComm;

#endif // VLINK_COMMUNICATION_H
