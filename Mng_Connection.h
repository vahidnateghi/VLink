#ifndef MNG_CONNECTION_H
#define MNG_CONNECTION_H

#include <QObject>
#include <VLink_Communication.h>

class Mng_Connection : public QObject
{
    Q_OBJECT
public:
    static Mng_Connection* Instance()
    {
        if( instance == NULL )
            instance = new Mng_Connection();
        return instance;
    }

    int AddNewCommunication();
    ShrdPtrComm Communication(int ID);
    template <class T>
    void AddPackToComm(int ID);


private:
    static Mng_Connection* instance;
    explicit Mng_Connection(QObject *parent = nullptr);

    QList<ShrdPtrComm> m_Comms;
};

#endif // MNG_CONNECTION_H
