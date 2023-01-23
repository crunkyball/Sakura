/*************************************************************
Sakura Game Framework : SaNetPacket.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_NET_PACKET_H
#define _SA_NET_PACKET_H

#include <Sakura/SaCore.h>
#include <Sakura/SaDebug.h>

namespace SakuraNet
{
    enum EPacketType
    {
        PACKET_UNKNOWN = 0,
        PACKET_CONNECT,
        PACKET_HEARTBEAT,
        PACKET_MAX  //Start your app packet types with this.
    };

    class SaNetPacket
    {
        friend class SaNetSocket;

    public:

        static const uint32_t MAX_PACKET_SIZE = 256;

        SaNetPacket();
        ~SaNetPacket();

        void WriteHeader(uint32_t uProtocolID, uint8_t uPacketType);
        bool ReadHeader(const uint32_t uProtocolID);

        void Write(uint8_t* pData, uint32_t uSize);
        void Read(uint8_t* pData, uint32_t uSize);

        uint8_t GetPacketType() const { return m_uPacketType; }

    private:
        uint8_t m_uPacketType;

        uint32_t m_uDataSize;
        uint8_t* m_pDataPtr;

        uint8_t m_data[MAX_PACKET_SIZE];
    };
}

#endif //_SA_NET_PACKET_H
