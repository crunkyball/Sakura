/*************************************************************
Sakura Game Framework : SaThread.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_THREAD_H
#define _SA_THREAD_H

#include <Sakura/SaCore.h>
#include PLATFORM_INCLUDE( SA_PLATFORM_DIR/SaThread_Platform.h )

namespace SakuraThread
{
    class SaThread
    {
        friend class SaThread_Platform;

    public:
        SaThread();
        ~SaThread();

        bool Initialise(const char* threadName, void* pFunction, void* pUserData = NULL, EThreadPriority threadPriority = PRIORITY_NORMAL);
        void Release();

        void Run();
        bool Wait(uint32_t timeout = 0);

        void Join();

        static void Sleep(uint32_t milliseconds) { SaThread_Platform::Sleep(milliseconds); }

    private:
        SaThread_Platform m_platformThread;

        const char* m_threadName;
        EThreadPriority m_threadPriority;
        void* m_pFunction;
        void* m_pUserData;
    };
}

#endif  //_SA_THREAD_H
