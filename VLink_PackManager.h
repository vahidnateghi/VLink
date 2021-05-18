#ifndef VLINK_PACKMANAGER_H
#define VLINK_PACKMANAGER_H

#include <QObject>
#include <VLink_Defines.h>
#include <VLink_Packs/VLink_Pack.h>
#include <stdio.h>

class VLink_PackManager : public QObject
{
    Q_OBJECT
public:
    explicit VLink_PackManager(QObject *parent = nullptr);

    void StopAnaloop();
    void AddPack(ShrdPtrPack pack);

    void setBufferMutex(const ShrdPtrMutex &BufferMutex);

private:
//    ShrdPtrBuffer m_Buffer;
    bool m_IsAnalysing;
    QList<ShrdPtrPack> m_Packs;
    ShrdPtrMutex m_BufferMutex;
    ShrdPtrBuffer m_Buffer;

public slots:
    void SltPuAnaLoop();
    void SltPuNewBytes(ShrdPtrByteArray Bytes);

signals:
    void SgNewPack(ShrdPtrPack);
};

#endif // VLINK_PACKMANAGER_H
