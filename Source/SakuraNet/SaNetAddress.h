/*************************************************************
Sakura Game Framework : SaNetAddress.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_NET_ADDRESS_H
#define _SA_NET_ADDRESS_H

#include <Sakura/SaCore.h>
#include "SaNet.h"

#define IP_ADDRESS_SIZE 16

namespace SakuraNet
{
    class SaNetAddress
    {
    public:
        SaNetAddress();
        SaNetAddress(char* sIPAddress, uint16_t uPort);
        SaNetAddress(sockaddr_in& rAddress);
        ~SaNetAddress();

        void Initialise();

        void CreateFromSockAddr(sockaddr_in& rAddress);
        bool CreateFromIPAndPort(char* sIPAddress, uint16_t uPort);

        bool IsValid() { return m_bValid; }

        char* GetIPAddrString() { return m_sIPAddress; }
        uint16_t GetPort() { return m_uPort; }

        sockaddr_in& GetSockAddr() { return m_address; }

    private:
        sockaddr_in m_address;
        bool m_bValid;

        char m_sIPAddress[IP_ADDRESS_SIZE];
        uint16_t m_uPort;
    };
}

#endif  //_SA_NET_ADDRESS_H
