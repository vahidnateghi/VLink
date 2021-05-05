#ifndef VLINK_PACKMANAGER_H
#define VLINK_PACKMANAGER_H

#include <QObject>
#include <VLink_Defines.h>
#include <Pack/VLink_Pack.h>

class VLink_PackManager : public QObject
{
    Q_OBJECT
public:
    explicit VLink_PackManager(QObject *parent = nullptr);

    void setBuffer(const ShrdPtrBuffer &Buffer);
    void StopAnaloop();
    void AddPack(ShrdPtrPack pack);

private:
    ShrdPtrBuffer m_Buffer;
    bool m_IsAnalysing;
    QList<ShrdPtrPack> m_Packs;

public slots:
    void SltPuAnaLoop();

signals:
    void SgNewPack(ShrdPtrPack);
};

#endif // VLINK_PACKMANAGER_H
