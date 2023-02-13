/*************************************************************
Sakura Game Framework : SaNetPacket.cpp
Author: Darrell Blake
*************************************************************/

#include "SaNetPacket.h"
#include <cstring>

using namespace SakuraNet;

SaNetPacket::SaNetPacket() :
    m_uPacketType(PACKET_UNKNOWN),
    m_uDataSize(0),
    m_pDataPtr(&m_data[0])
{
}

SaNetPacket::~SaNetPacket()
{
}

void SaNetPacket::WriteHeader(uint32_t uProtocolID, uint8_t uPacketType)
{
    SA_ASSERT(m_pDataPtr == &m_data[0], "Incorrect data pointer position.");

    m_uPacketType = uPacketType;

    Write((uint8_t*)&uProtocolID, sizeof(uint32_t));
    Write(&uPacketType, sizeof(uint8_t));
}

bool SaNetPacket::ReadHeader(const uint32_t uProtocolID)
{
    SA_ASSERT(m_pDataPtr == &m_data[0], "Incorrect data pointer position.");

    uint32_t protocolID = 0;
    Read((uint8_t*)&protocolID, sizeof(protocolID));

    if (uProtocolID == protocolID)
    {
        uint8_t uPacketType;
        Read(&uPacketType, sizeof(uPacketType));

        m_uPacketType = uPacketType;

        return true;
    }

    return false;
}

void SaNetPacket::Write(uint8_t* pData, uint32_t uSize)
{
    SA_ASSERT(m_uPacketType > PACKET_UNKNOWN, "Unknown packet type.");
    SA_ASSERT(pData, "No data.");
    SA_ASSERT(uSize < (MAX_PACKET_SIZE - m_uDataSize), "Data size too large.");

    memcpy(m_pDataPtr, pData, uSize);

    m_pDataPtr += uSize;
    m_uDataSize += uSize;
}

void SaNetPacket::Read(uint8_t* pData, uint32_t uSize)
{
    SA_ASSERT(pData, "No data.");
    SA_ASSERT(uSize <= m_uDataSize, "Buffer not large enough.");

    memcpy(pData, m_pDataPtr, uSize);

    m_pDataPtr += uSize;
}
