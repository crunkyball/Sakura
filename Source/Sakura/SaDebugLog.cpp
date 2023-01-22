/*************************************************************
Sakura Game Framework : SaDebugLog.h
Author: Darrell Blake
*************************************************************/

#include "SaDebugLog.h"
#include <cstring>
#include <cstdio>

using namespace Sakura;
using namespace SakuraThread;

#ifdef SA_BUILD_DEBUG
uint32_t SaDebugLog::ms_messageCount = 0;
char SaDebugLog::ms_messages[NUM_MESSAGES][MAX_MESSAGE_LEN];
SaMutex SaDebugLog::ms_messageMutex;
#endif

void SaDebugLog::Add(const char* pFmt, ...)
{
#ifdef SA_BUILD_DEBUG
    ms_messageMutex.Lock();

    uint32_t messageIdx = ms_messageCount % NUM_MESSAGES;
    memset(ms_messages[messageIdx], 0, MAX_MESSAGE_LEN);

    va_list args;
    va_start(args, pFmt);
    vsprintf(ms_messages[messageIdx], pFmt, args);
    va_end(args);

    ms_messageCount++;

    ms_messageMutex.Unlock();
#endif
}
