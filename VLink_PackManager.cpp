#include "VLink_PackManager.h"
#include <QDataStream>

VLink_PackManager::VLink_PackManager(QObject *parent) : QObject(parent)
{
    m_IsAnalysing = false;
}

void VLink_PackManager::setBuffer(const ShrdPtrBuffer &Buffer)
{
    m_Buffer = Buffer;
}

void VLink_PackManager::StopAnaloop()
{
    m_IsAnalysing = false;
}

void VLink_PackManager::AddPack(ShrdPtrPack pack)
{
    m_Packs.append( pack );
}

void VLink_PackManager::SltPuAnaLoop()
{
    if( m_IsAnalysing == true )
        return;

    m_IsAnalysing = true;
    while( m_IsAnalysing )
    {
        AnalyzeResult Res = AnaRes_UnKnown;

        do
        {
            if( m_Packs.count() == 0 )
            {
                m_Buffer.data()->clear();
                Res = AnaRes_TooShort;
                continue;
            }

            for( int i = 0; i < m_Packs.count(); i++ )
            {
                AnalyzeResult tRes = m_Packs.at(i)->AnalyzeBytes( m_Buffer.data() );
                if( tRes == AnaRes_Error )
                {
                    if( Res != AnaRes_TooShort )
                        Res = tRes;
                }
                else if( tRes == AnaRes_Ok )
                {
                    ShrdPtrPack NewPack = ShrdPtrPack( m_Packs.at(i)->MakeCopy() );
                    NewPack.data()->FillPack( m_Buffer.data() );
                    m_Buffer.data()->erase( m_Buffer.data()->begin(), m_Buffer.data()->begin() + NewPack.data()->PackSize() );

                    emit SgNewPack( NewPack );
                }
            }

            if( Res == AnaRes_Error )
            {
                m_Buffer.data()->pop_back();
            }

        } while( Res != AnaRes_TooShort );
    }
}
