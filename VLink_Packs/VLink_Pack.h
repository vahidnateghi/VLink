#ifndef VLINK_PACK_H
#define VLINK_PACK_H

#include "VLink_Defines.h"
#include <QObject>



class VLink_Pack : public QObject
{
    Q_OBJECT
public:
    explicit VLink_Pack(QObject *parent = nullptr);
    virtual AnalyzeResult AnalyzeBytes( ShrdPtrBuffer ) { return AnaRes_UnKnown; }
    virtual void FillPack( std::vector<char>* ) {}
    virtual VLink_Pack* MakeCopy() { return nullptr; }
    virtual int PackSize() { return 0; }
    virtual QByteArray GetBytes() {return QByteArray(); }

protected:

private:
    static int m_IdCounter;
    int m_ID;
};

typedef QSharedPointer<VLink_Pack> ShrdPtrPack;
Q_DECLARE_METATYPE(ShrdPtrPack)

#endif // VLINK_PACK_H
