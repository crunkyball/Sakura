/*************************************************************
Sakura Game Framework : SaNetConnection.cpp
Author: Darrell Blake
*************************************************************/

#include "SaNetConnection.h"

using namespace SakuraNet;

SaNetConnection::SaNetConnection()
{
    Initialise();

    m_uProtocolID = 0;
    m_appPacketCallback = NULL;
}

SaNetConnection::SaNetConnection(uint32_t uProtocolID, RecvAppPacketCallback appCallback)
{
    Initialise();

    m_uProtocolID = uProtocolID;
    m_appPacketCallback = appCallback;
}

SaNetConnection::~SaNetConnection()
{
}

void SaNetConnection::Initialise()
{
    m_eState = STATE_DISCONNECTED;
    m_connectedAddress.Initialise();
    m_bHost = false;
    m_uHeartBeatTime = 0;
    m_uTimeout = 0;
}

bool SaNetConnection::Open(uint16_t uPort)
{
    SA_ASSERT(!m_socket.IsOpen(), "Socket already open.");
    return m_socket.Open(uPort);
}

void SaNetConnection::Close()
{
    Initialise();
    m_socket.Close();
}

void SaNetConnection::WaitForConnection()
{
    SA_ASSERT(m_bHost, "I'm not the host.");
    m_eState = STATE_CONNECTING;
}

void SaNetConnection::ConnectTo(SaNetAddress& rAddress)
{
    SA_ASSERT(!m_bHost, "I'm the host.");

    m_eState = STATE_CONNECTING;

    uint8_t data = 0;

    SaNetPacket packet;
    packet.WriteHeader(m_uProtocolID, PACKET_CONNECT);
    packet.Write(&data, sizeof(data));

    bool bSuccess = SendPacket(rAddress, packet);

    if (bSuccess)
    {
        SA_PRINTF("Connection packet sent...\n");
    }
    else
    {
        SA_PRINTF("Couldn't send packet. Closing connection.\n");
        Close();
    }
}

bool SaNetConnection::SendPacket(SaNetAddress& rSendTo, SaNetPacket& rPacket)
{
    SA_ASSERT(m_eState > STATE_DISCONNECTED, "Incorrect state.");
    SA_ASSERT(m_socket.IsOpen(), "Socket not open.");

    bool bSuccess = false;

#ifdef NET_SIMULATION_ENABLED
    bSuccess = m_netSimulation.SendPacket(m_socket, rSendTo, rPacket);
#else
    bSuccess = m_socket.Send(rSendTo, rPacket);
#endif

    if (bSuccess)
    {
        m_uHeartBeatTime = 0;
    }

    return bSuccess;
}

bool SaNetConnection::SendPacketToConnected(SaNetPacket& rPacket)
{
    return SendPacket(m_connectedAddress, rPacket);
}

void SaNetConnection::ProcessPacketsIn()
{
    SaNetAddress sender;
    SaNetPacket packet;

    int32_t bytesRead = ReceivePacket(sender, packet);

    if (bytesRead > 0)
    {
        OnReceivedPacket(sender, packet);
    }
}

int32_t SaNetConnection::ReceivePacket(SaNetAddress& rSender, SaNetPacket& rPacket)
{
    SA_ASSERT(m_eState > STATE_DISCONNECTED, "Incorrect state.");
    SA_ASSERT(m_socket.IsOpen(), "Socket not open.");

#ifdef NET_SIMULATION_ENABLED
    int32_t bytesRead = m_netSimulation.ReceivePacket(m_socket, rSender, rPacket);
#else
    int32_t bytesRead = m_socket.Receive(rSender, rPacket);
#endif

    if (bytesRead < sizeof(uint32_t))
    {
        bytesRead = 0;
    }
    else
    {
        //Check packet header against protocol ID.
        bool validPacket = rPacket.ReadHeader(m_uProtocolID);

        SA_WARNING(validPacket, "Received packet with incorrect protocol ID.");

        //If it's not one of our packets then discount it.
        if (!validPacket)
        {
            bytesRead = 0;
        }
    }

    return bytesRead;
}

void SaNetConnection::OnReceivedPacket(SaNetAddress& rSender, SaNetPacket& rPacket)
{
    m_uTimeout = 0;

    if (rPacket.GetPacketType() < PACKET_MAX)
    {
        if (m_eState == STATE_CONNECTING)
        {
            m_connectedAddress = rSender;
            m_eState = STATE_CONNECTED;
        }
        else if (m_eState == STATE_CONNECTED)
        {
            //SA_PRINTF("Packet received!\n");
        }
        else
        {
            SA_FAIL("Shouldn't be receiving packets in any other state.");
        }
    }
    else
    {
        //Pass the packet to the app to handle.
        if (m_appPacketCallback)
        {
            m_appPacketCallback(rPacket);
        }
    }
}

void SaNetConnection::UpdateHeartbeat(uint32_t uDeltaTime)
{
    SA_ASSERT(m_eState == STATE_CONNECTED, "Invalid state.");

    m_uHeartBeatTime += uDeltaTime;

    if (m_uHeartBeatTime > 100)
    {
        uint8_t data = 0;

        SaNetPacket packet;
        packet.WriteHeader(m_uProtocolID, PACKET_HEARTBEAT);
        packet.Write(&data, sizeof(data));
        
        bool bSuccess = SendPacket(m_connectedAddress, packet);
        m_uHeartBeatTime = 0;
    }
}

void SaNetConnection::Update(uint32_t uDeltaTime)
{
    switch(m_eState)
    {
        case STATE_DISCONNECTED:
            break;
        case STATE_CONNECTING:
            ProcessPacketsIn();
            break;
        case STATE_CONNECTED:

            UpdateHeartbeat(uDeltaTime);

            ProcessPacketsIn();

            if (m_uTimeout > CONNECTION_TIMEOUT)
            {
                SA_PRINTF("Connection timed out!\n");
                Close();
            }

            m_uTimeout += uDeltaTime;

            break;
        default:
            SA_FAIL("Unknown state.");
    }

#ifdef NET_SIMULATION_ENABLED
    m_netSimulation.Update(m_socket, uDeltaTime);
#endif
}
