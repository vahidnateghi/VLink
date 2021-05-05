#ifndef VLINK_H
#define VLINK_H

#include <QObject>
#include "LinkInfo/LinkInfo.h"
#include <VLink_Defines.h>

class VLink : public QObject
{
    Q_OBJECT
public:
    explicit VLink(QObject *parent = nullptr);

    virtual void FinLink() = 0;
    virtual int SendBytes(const QByteArray& Bytes) = 0;

    int ID() const;

public slots:
    virtual void InitLink( ShrdPtrInfo ) = 0;

signals:
    void SgNewInput(ShrdPtrByteArray);

protected:
    ShrdPtrInfo   m_LinkInfo;

private:
    int         m_ID;
    static int m_IdCounter;
};

typedef QSharedPointer<VLink> ShrdPtrLink;
Q_DECLARE_METATYPE(ShrdPtrLink)

#endif // VLINK_H
