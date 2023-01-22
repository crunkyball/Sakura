/*************************************************************
Sakura Game Framework : SaMutex.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_MUTEX_H
#define _SA_MUTEX_H

#include <Sakura/SaCore.h>
#include PLATFORM_INCLUDE( SA_PLATFORM_DIR/SaMutex_Platform.h )

namespace SakuraThread
{
    class SaMutex
    {
        friend class SaMutex_Platform;
        friend class SaConditionVariable;

    public:
        SaMutex();
        ~SaMutex();

        void Lock();
        bool TryLock();
        void Unlock();

    private:
        SaMutex_Platform m_platformMutex;
    };
}

#endif  //_SA_MUTEX_H
