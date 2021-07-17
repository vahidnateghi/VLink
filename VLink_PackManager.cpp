#include "VLink_PackManager.h"
#include <QDataStream>
#include <QMutex>
#include <iostream>

VLink_PackManager::VLink_PackManager(QObject *parent) : QObject(parent)
{
    m_IsAnalysing = false;
    m_Buffer = QSharedPointer<std::vector<char>>(new std::vector<char>());
}

void VLink_PackManager::StopAnaloop()
{
    m_IsAnalysing = false;
}

void VLink_PackManager::AddPack(ShrdPtrPack pack)
{
    m_Packs.append( pack );
}

void VLink_PackManager::setBufferMutex(const ShrdPtrMutex &BufferMutex)
{
    m_BufferMutex = BufferMutex;
}

void VLink_PackManager::SltPuAnaLoop()
{
//    if( m_IsAnalysing == true )
//        return;

//    m_IsAnalysing = true;
//    while( m_IsAnalysing )
//    {
//    }
}

void VLink_PackManager::SltPuNewBytes(ShrdPtrByteArray Bytes)
{
    for( int i = 0; i < Bytes.data()->size(); i++ )
        m_Buffer.data()->push_back(Bytes.data()->at(i));

    AnalyzeResult Res = AnaRes_UnKnown;

    do
    {
        if( m_Packs.count() == 0 )
        {
            m_Buffer.data()->pop_back();
            Res = AnaRes_TooShort;
            continue;
        }

        if( m_Buffer.data()->size() == 0 )
        {
            Res = AnaRes_TooShort;
            continue;
        }

        for( int i = 0; i < m_Packs.count(); i++ )
        {
            AnalyzeResult tRes = m_Packs.at(i)->AnalyzeBytes( m_Buffer );
            if( tRes == AnaRes_Error )
            {
                if( Res != AnaRes_TooShort )
                    Res = tRes;
            }
            else if( tRes == AnaRes_Ok )
            {
                ShrdPtrPack NewPack = ShrdPtrPack( m_Packs.at(i)->MakeCopy() );
                NewPack.data()->FillPack( m_Buffer.data() );
                m_BufferMutex.data()->lock();
                m_Buffer.data()->erase( m_Buffer.data()->begin(), m_Buffer.data()->begin() + NewPack.data()->PackSize() );
                m_BufferMutex.data()->unlock();

                emit SgNewPack( NewPack );
            }
            else if( tRes == AnaRes_TooShort )
            {
                Res = tRes;
            }
        }

        if( Res == AnaRes_Error  && m_Buffer.data()->size() > 0 )
        {
            m_BufferMutex.data()->lock();
            m_Buffer.data()->erase( m_Buffer.data()->begin() );
            m_BufferMutex.data()->unlock();
        }

    } while( Res != AnaRes_TooShort );
}
