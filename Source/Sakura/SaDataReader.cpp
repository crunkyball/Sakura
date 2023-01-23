#include "SaDataReader.h"

using namespace Sakura;

SaDataReader::SaDataReader(const uint8_t* pPtr) :
    m_pPtr(pPtr)
{
}

uint8_t SaDataReader::Read8()
{
    return *m_pPtr++;
}

uint16_t SaDataReader::Read16()
{
    uint16_t val = *reinterpret_cast<const uint16_t*>(m_pPtr);
    m_pPtr += sizeof(val);
    return val;
}

uint32_t SaDataReader::Read32()
{
    uint32_t val = *reinterpret_cast<const uint32_t*>(m_pPtr);
    m_pPtr += sizeof(val);
    return val;
}

float SaDataReader::ReadFloat()
{
    float val = *reinterpret_cast<const float*>(m_pPtr);
    m_pPtr += sizeof(val);
    return val;
}

const char* SaDataReader::ReadString()
{
    const char* pStr = reinterpret_cast<const char*>(m_pPtr);

    while(pStr)
        pStr++;

    return pStr;
}
