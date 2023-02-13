/*************************************************************
Sakura Game Framework : SaNetSocket.cpp
Author: Darrell Blake
*************************************************************/

#include "SaNet.h"
#include "SaNetSocket.h"

#ifndef SA_PLATFORM_WINDOWS
#include <unistd.h>
#endif

using namespace SakuraNet;

SaNetSocket::SaNetSocket() :
    m_handle(0)
{
}

SaNetSocket::~SaNetSocket()
{
    Close();
}

bool SaNetSocket::Open(uint16_t uPort)
{
    SA_ASSERT(uPort > 1024, "First 1024 ports are reserved.");
    SA_ASSERT(!IsOpen(), "Socket already open.");

    //Create socket.
    SOCKET handle = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (handle == -1)
        return false;

    m_handle = handle;

    //Bind to port.
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(uPort);

    int32_t result = bind(m_handle, (const sockaddr*)&address, sizeof(sockaddr_in));

    if (result == -1)
        return false;

    //Set non-blocking I/O.
#ifdef SA_PLATFORM_WINDOWS
    DWORD nonBlocking = 1;
    if (ioctlsocket(m_handle, FIONBIO, &nonBlocking) != 0)
    {
        Close();
        return false;
    }
#else
    int32_t nonBlocking = 1;
    if (fcntl(m_handle, F_SETFL, O_NONBLOCK, nonBlocking) == -1)
    {
        Close();
        return false;
    }
#endif

    return true;
}

void SaNetSocket::Close()
{
    if (m_handle != 0)
    {
#ifdef SA_PLATFORM_WINDOWS
        closesocket(m_handle);
#else
        close(m_handle);
#endif
        m_handle = 0;
    }
}

bool SaNetSocket::IsOpen()
{
    return m_handle != 0;
}

bool SaNetSocket::Send(const SaNetAddress& rAddress, const SaNetPacket& rPacket) const
{
    SA_ASSERT(rAddress.IsValid(), "Invalid address.");
    SA_ASSERT(m_handle != 0, "Invalid socket handle.");

    if (m_handle == 0)
        return false;

    int32_t sentBytes = sendto(m_handle, reinterpret_cast<const char*>(rPacket.m_data), rPacket.m_uDataSize, 0, reinterpret_cast<const sockaddr*>(&rAddress.GetSockAddr()), sizeof(sockaddr_in));

    if (sentBytes < 0)
    {
#ifdef SA_PLATFORM_WINDOWS
        int32_t errorNum = WSAGetLastError();
#else
        int32_t errorNum = errno;
#endif

        SA_PRINTF("Sending packet error! Error number %i\n", errorNum);
    }

    return sentBytes == rPacket.m_uDataSize;
}

int32_t SaNetSocket::Receive(SaNetAddress& rOutAddress, SaNetPacket& rOutPacket) const
{
    SA_ASSERT(m_handle != 0, "Invalid socket handle.");

    if (m_handle == 0)
        return -1;

    sockaddr_in from;
    socklen_t fromSize = sizeof(from);

    int32_t receivedBytes = recvfrom(m_handle, reinterpret_cast<char*>(rOutPacket.m_data), SaNetPacket::MAX_PACKET_SIZE, 0, reinterpret_cast<sockaddr*>(&from), &fromSize);

    if (receivedBytes > 0)
    {
        rOutAddress.CreateFromSockAddr(from);
        rOutPacket.m_uDataSize = receivedBytes;
    }
    else if (receivedBytes == -1)
    {
        receivedBytes = 0;

#ifdef SA_PLATFORM_WINDOWS
        int32_t errorNum = WSAGetLastError();

        if (errorNum != WSAEWOULDBLOCK)
        {
#else
        int32_t errorNum = errno;

        if (errorNum != EWOULDBLOCK)
        {
#endif
            SA_PRINTF("Receive packet error! Error number %i\n", errorNum);
        }
    }

    return receivedBytes;
}
