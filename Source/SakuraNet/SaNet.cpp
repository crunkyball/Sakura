/*************************************************************
Sakura Game Framework : SaNet.cpp
Author: Darrell Blake
*************************************************************/

#include "SaNet.h"

using namespace SakuraNet;

SaNet::SaNet()
{
}

SaNet::~SaNet()
{
}

bool SaNet::InitialiseSockets()
{
#ifdef SA_PLATFORM_WINDOWS
    WSADATA WsaData;
    return WSAStartup(MAKEWORD(2,2), &WsaData) == NO_ERROR;
#endif

    return true;
}

void SaNet::ShutdownSockets()
{
#ifdef SA_PLATFORM_WINDOWS
    WSACleanup();
#endif
}
