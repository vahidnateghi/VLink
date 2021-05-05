#ifndef VLINK_COMMUNICATION_H
#define VLINK_COMMUNICATION_H

#include <QObject>
#include <VLink_LinkManager.h>
#include <VLink_PackManager.h>
#include <VLink_Defines.h>
#include <Pack/VLink_Pack.h>
#include <QThread>

class VLink_Communication : public QObject
{
    Q_OBJECT
public:
    explicit VLink_Communication(QObject *parent = nullptr);
    void AddLink(LinkType Type, ShrdPtrInfo Info);
    void SendPack(VLink_Pack &pack );
    template <class T>
    void AddPack()
    {
        m_PackManager.AddPack( ShrdPtrPack( new T() ) );
    }

    int ID() const;

private:
    static int m_IdCounter;
    VLink_LinkManager m_LinkManager;
    VLink_PackManager m_PackManager;
    int m_ID;
    ShrdPtrBuffer m_Buffer;
    QThread* m_PackMngrThread;


signals:
    void SgNewPack(ShrdPtrPack);
    void SgStart();
};

typedef QSharedPointer<VLink_Communication> ShrdPtrComm;

#endif // VLINK_COMMUNICATION_H
