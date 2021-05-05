#include "Mng_Connection.h"

Mng_Connection* Mng_Connection::instance = NULL;

Mng_Connection::Mng_Connection(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<ShrdPtrByteArray>("ShrdPtrByteArray");
    qRegisterMetaType<ShrdPtrPack>("ShrdPtrPack");
    qRegisterMetaType<ShrdPtrInfo>("ShrdPtrInfo");
}

int Mng_Connection::AddNewCommunication()
{
    ShrdPtrComm newComm = ShrdPtrComm(new VLink_Communication());

    m_Comms.append( newComm );
}

ShrdPtrComm Mng_Connection::Communication(int ID)
{
    for( int i = 0; i < m_Comms.count(); i++ )
    {
        if( m_Comms.at(i).data()->ID() == ID )
            return m_Comms.at(i);
    }

    return ShrdPtrComm();
}

template<class T>
void Mng_Connection::AddPackToComm(int ID)
{
    for( int i = 0; i < m_Comms.count(); i++ )
    {
        if( m_Comms.at(i).data()->ID() == ID )
        {
            m_Comms.at(i).data()->AddPack<T>();
        }
    }
}
