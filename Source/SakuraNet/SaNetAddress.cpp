/*************************************************************
Sakura Game Framework : SaNetAddress.cpp
Author: Darrell Blake
*************************************************************/

#include "SaNetAddress.h"
#include <cstring>

using namespace SakuraNet;

SaNetAddress::SaNetAddress()
{
    Initialise();
}

SaNetAddress::SaNetAddress(const char* sIPAddress, uint16_t uPort)
{
    CreateFromIPAndPort(sIPAddress, uPort);
}

SaNetAddress::SaNetAddress(const sockaddr_in& rAddress)
{
    CreateFromSockAddr(rAddress);
}

SaNetAddress::~SaNetAddress()
{
}

void SaNetAddress::Initialise()
{
    m_bValid = false;
    memset(m_sIPAddress, 0, IP_ADDRESS_SIZE);
    memset(&m_address, 0, sizeof(m_address));
    m_uPort = 0;
}

void SaNetAddress::CreateFromSockAddr(const sockaddr_in& rAddress)
{
    Initialise();

    inet_ntop(AF_INET, &rAddress.sin_addr, m_sIPAddress, IP_ADDRESS_SIZE);

    m_uPort = ntohs(rAddress.sin_port);
    m_address = rAddress;

    m_bValid = true;
}

bool SaNetAddress::CreateFromIPAndPort(const char* sIPAddress, uint16_t uPort)
{
    Initialise();

    bool bSuccess = inet_pton(AF_INET, sIPAddress, &m_address.sin_addr) == 1;

    m_address.sin_family = AF_INET;
    m_address.sin_port = htons(uPort);

    if (bSuccess)
    {
        m_bValid = true;
        strcpy_s(m_sIPAddress, IP_ADDRESS_SIZE, sIPAddress);
        m_uPort = uPort;
    }
    else
    {
#ifdef SA_PLATFORM_WINDOWS
        int32_t errorNum = WSAGetLastError();
#else
        int32_t errorNum = errno;
#endif

        SA_PRINTF("Error: Couldn't create net address! Error number %i\n", errorNum);
    }

    return bSuccess;
}
