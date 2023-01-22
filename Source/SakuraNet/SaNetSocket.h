/*************************************************************
Sakura Game Framework : SaNetSocket.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_NET_SOCKET_H
#define _SA_NET_SOCKET_H

#include <Sakura/SaCore.h>
#include "SaNetAddress.h"
#include "SaNetPacket.h"

namespace SakuraNet
{
#ifndef SA_PLATFORM_WINDOWS
    typedef int32_t SOCKET;
#endif

    class SaNetSocket
    {
    public:
        SaNetSocket();
        ~SaNetSocket();

        bool Open(uint16_t uPort);
        void Close();
        bool IsOpen();

        bool Send(SaNetAddress& rAddress, SaNetPacket& rPacket);
        int32_t Receive(SaNetAddress& rAddress, SaNetPacket& rPacket);

    private:
        SOCKET m_handle;
    };
}

#endif
