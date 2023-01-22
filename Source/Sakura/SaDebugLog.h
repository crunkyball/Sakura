/*************************************************************
Sakura Game Framework : SaDebugLog.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_DEBUG_LOG_H
#define _SA_DEBUG_LOG_H

#include "SaCore.h"
#include <SakuraThread/SaMutex.h>

namespace Sakura
{
    class SaDebugLog
    {
    public:
        static void Add(const char* pFmt, ...);

    private:
#ifdef SA_BUILD_DEBUG
        //256k for debug log. I should probably make this class more elegant 
        //at some point but I'm not too fussed with it being debug only.
        static const uint32_t MAX_MESSAGE_LEN = 256;
        static const uint32_t NUM_MESSAGES = 1024;

        static uint32_t             ms_messageCount;
        static SakuraThread::SaMutex    ms_messageMutex;
        static char                 ms_messages[NUM_MESSAGES][MAX_MESSAGE_LEN];
#endif
    };
}

#endif  //_SA_DEBUG_LOG_H
