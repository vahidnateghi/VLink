#ifndef LINKINFO_H
#define LINKINFO_H

#include <QObject>
#include <QSharedPointer>

class LinkInfo : public QObject
{
    Q_OBJECT
public:
    explicit LinkInfo(QObject *parent = nullptr);

};

typedef QSharedPointer<LinkInfo> ShrdPtrInfo;
Q_DECLARE_METATYPE( ShrdPtrInfo )

#endif // LINKINFO_H
