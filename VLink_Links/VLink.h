#ifndef VLINK_H
#define VLINK_H

#include <QObject>
#include "VLink_Infos/LinkInfo.h"
#include <VLink_Defines.h>

class VLink : public QObject
{
    Q_OBJECT
public:
    explicit VLink(QObject *parent = nullptr);


    int ID() const;

    ShrdPtrInfo LinkInfo() const;

    void setLinkInfo(const ShrdPtrInfo &LinkInfo);

    bool IsInitialized() const;

public slots:
    virtual void InitLink(ShrdPtrInfo info);
    virtual int SendBytes(const QByteArray& Bytes) = 0;
    virtual void Start() = 0;
    virtual void FinLink() = 0;

signals:
    void SgNewInput(ShrdPtrByteArray);
    void SgStarted();
    void SgStopped();

protected:
    ShrdPtrInfo     m_LinkInfo;
    bool m_IsInitialized;

private:
    int         m_ID;
    static int m_IdCounter;
};

typedef QSharedPointer<VLink> ShrdPtrLink;
Q_DECLARE_METATYPE(ShrdPtrLink)

#endif // VLINK_H
