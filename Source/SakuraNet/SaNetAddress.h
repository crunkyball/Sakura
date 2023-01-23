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
        SaNetAddress(const char* sIPAddress, uint16_t uPort);
        SaNetAddress(const sockaddr_in& rAddress);
        ~SaNetAddress();

        void Initialise();

        void CreateFromSockAddr(const sockaddr_in& rAddress);
        bool CreateFromIPAndPort(const char* sIPAddress, uint16_t uPort);

        bool IsValid() const { return m_bValid; }

        const char* GetIPAddrString() const { return m_sIPAddress; }
        uint16_t GetPort() const { return m_uPort; }

        const sockaddr_in& GetSockAddr() const { return m_address; }

    private:
        sockaddr_in m_address;
        bool m_bValid;

        char m_sIPAddress[IP_ADDRESS_SIZE];
        uint16_t m_uPort;
    };
}

#endif  //_SA_NET_ADDRESS_H
