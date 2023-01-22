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

SaNetAddress::SaNetAddress(char* sIPAddress, uint16_t uPort)
{
    CreateFromIPAndPort(sIPAddress, uPort);
}

SaNetAddress::SaNetAddress(sockaddr_in& rAddress)
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

void SaNetAddress::CreateFromSockAddr(sockaddr_in& rAddress)
{
    Initialise();

#ifdef SA_PLATFORM_WINDOWS
    DWORD resultSize = IP_ADDRESS_SIZE;
    strcpy(m_sIPAddress, inet_ntoa(rAddress.sin_addr));
#else
    inet_ntop(AF_INET, &rAddress.sin_addr, m_sIPAddress, IP_ADDRESS_SIZE);
#endif

    m_uPort = ntohs(rAddress.sin_port);
    m_address = rAddress;

    m_bValid = true;
}

bool SaNetAddress::CreateFromIPAndPort(char* sIPAddress, uint16_t uPort)
{
    Initialise();

#ifdef SA_PLATFORM_WINDOWS
    int32_t iSize = sizeof(sockaddr);
    bool bSuccess = WSAStringToAddress(sIPAddress, AF_INET, NULL, (sockaddr*)&m_address, &iSize) == 0;

#else
    bool bSuccess = inet_pton(AF_INET, sIPAddress, &m_address.sin_addr) == 1;
#endif

    m_address.sin_family = AF_INET;
    m_address.sin_port = htons(uPort);

    if (bSuccess)
    {
        m_bValid = true;
        strcpy(m_sIPAddress, sIPAddress);
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
