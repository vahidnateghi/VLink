#ifndef VLINKDEFINES_H
#define VLINKDEFINES_H

#include <QSharedPointer>

typedef QSharedPointer<QByteArray> ShrdPtrByteArray;
Q_DECLARE_METATYPE(ShrdPtrByteArray)

typedef QSharedPointer<std::vector<char>> ShrdPtrBuffer;
Q_DECLARE_METATYPE(ShrdPtrBuffer)

enum AnalyzeResult
{
    AnaRes_Ok,
    AnaRes_Error,
    AnaRes_TooShort,
    AnaRes_UnKnown
};

enum LinkType
{
    Link_UDP
};

#endif // VLINKDEFINES_H
