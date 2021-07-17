#ifndef VLINKDEFINES_H
#define VLINKDEFINES_H

#include <QSharedPointer>
#include <QMutex>

typedef QSharedPointer<QByteArray> ShrdPtrByteArray;
Q_DECLARE_METATYPE(ShrdPtrByteArray)

typedef QSharedPointer<std::vector<char>> ShrdPtrBuffer;
Q_DECLARE_METATYPE(ShrdPtrBuffer)

typedef QSharedPointer<QMutex> ShrdPtrMutex;
Q_DECLARE_METATYPE(ShrdPtrMutex)

enum AnalyzeResult
{
    AnaRes_Ok,
    AnaRes_Error,
    AnaRes_TooShort,
    AnaRes_UnKnown
};

enum LinkType
{
    Link_UDP,
    Link_UDPRaw,
    Link_Serial
};

#endif // VLINKDEFINES_H
