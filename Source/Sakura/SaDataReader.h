/*************************************************************
Sakura Game Framework : SaDataReader.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_DATA_READER_H
#define _SA_DATA_READER_H

#include "SaCore.h"

namespace Sakura
{
    class SaDataReader
    {
    public:
        SaDataReader(const uint8_t* pPtr);

        uint8_t Read8();
        uint16_t Read16();
        uint32_t Read32();
        float ReadFloat();
        const char* ReadString();

    private:
        const uint8_t* m_pPtr;
    };
}

#endif  //_SA_DATA_READER_H
