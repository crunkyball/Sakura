/*************************************************************
Sakura Game Framework : SaMutex_Platform.h
Author: Darrell Blake

Windows platform implementation for SaMutex.

Use a light mutex wherever possible. That's why I'm using 
critical section.
*************************************************************/

#ifndef _SA_MUTEX_PLATFORM_H
#define _SA_MUTEX_PLATFORM_H

#include <Sakura/SaCore.h>
#include <Windows.h>

namespace SakuraThread
{
    class SaMutex_Platform
    {
    public:
        SaMutex_Platform();
        ~SaMutex_Platform();

        void Lock();
        bool TryLock();
        void Unlock();

        CRITICAL_SECTION& GetCriticalSection();

    private:
        CRITICAL_SECTION m_criticalSection;
    };
}

#endif  //_SA_MUTEX_PLATFORM_H
