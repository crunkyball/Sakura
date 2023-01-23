/*************************************************************
Sakura Game Framework : SakuraNet.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_NET_H
#define _SA_NET_H

#include <Sakura/SaCore.h>

#ifdef SA_PLATFORM_WINDOWS
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <errno.h>
#endif

#include <Sakura/SaDebug.h>

namespace SakuraNet
{
    enum
    {
        CONNECTION_TIMEOUT = 10*1000
    };

    class SaNet
    {
    public:
        SaNet();
        ~SaNet();

        static bool InitialiseSockets();
        static void ShutdownSockets();
    };
}

#endif
