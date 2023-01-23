/*************************************************************
Sakura Game Framework : SaNetConnection.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_NET_CONNECTION_H
#define _SA_NET_CONNECTION_H

#include <Sakura/SaCore.h>
#include "SaNetSocket.h"
#include "SaNetSimulation.h"

namespace SakuraNet
{
    class SaNetConnection
    {
    public:
        enum EState
        {
            STATE_DISCONNECTED = 0,
            STATE_CONNECTING,
            STATE_CONNECTED
        };

        typedef void (*RecvAppPacketCallback)(SaNetPacket& rPacket);

        SaNetConnection();
        SaNetConnection(uint32_t uProtocolID, RecvAppPacketCallback appCallback);
        ~SaNetConnection();

        void Initialise();
        bool Open(uint16_t uPort);
        void SetHost(bool bHost) { m_bHost = bHost; }
        bool IsHost() { return m_bHost; }
        bool IsConnected() { return m_eState == STATE_CONNECTED; }
        bool IsDisconnected() { return m_eState == STATE_DISCONNECTED; }

        void WaitForConnection();
        void ConnectTo(SaNetAddress& rAddress);

        void Update(uint32_t uDeltaTime);
        void UpdateHeartbeat(uint32_t uDeltaTime);

        bool SendPacket(SaNetAddress& rSendTo, SaNetPacket& rPacket);
        bool SendPacketToConnected(SaNetPacket& rPacket);

        void ProcessPacketsIn();
        int32_t ReceivePacket(SaNetAddress& rSender, SaNetPacket& rPacket);
        void OnReceivedPacket(const SaNetAddress& rSender, SaNetPacket& rPacket);

        SaNetSocket& GetSocket() { return m_socket; }
        SaNetAddress& GetConnectedAddress() { return m_connectedAddress; }

#ifdef NET_SIMULATION_ENABLED
        SaNetSimulation& GetNetSimulation() { return m_netSimulation; }
#endif

    private:
        void Close();

#ifdef NET_SIMULATION_ENABLED
        SaNetSimulation m_netSimulation;
#endif

        SaNetSocket m_socket;
        EState m_eState;
        bool m_bHost;
        uint32_t m_uProtocolID;
        SaNetAddress m_connectedAddress;
        uint32_t m_uHeartBeatTime;
        uint32_t m_uTimeout;

        RecvAppPacketCallback m_appPacketCallback;
    };
}

#endif //_SA_NET_CONNECTION_H
