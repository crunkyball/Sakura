/*************************************************************
Sakura Game Framework : SaThread_Platform.h
Author: Darrell Blake

Windows platform implementation for SaThread.
*************************************************************/

#ifndef _SA_THREAD_PLATFORM_H
#define _SA_THREAD_PLATFORM_H

#include <Sakura/SaCore.h>
#include <Windows.h>
#include "../../SaThreadDefines.h"

namespace SakuraThread
{
    class SaThread;

    class SaThread_Platform
    {
    public:
        SaThread_Platform(SaThread* pParent);
        ~SaThread_Platform();

        bool Initialise();
        void Release();

        void Run();
        bool Wait(uint32_t timeout);

        void Join();

        static void Sleep(uint32_t milliseconds);

    private:
        SaThread*   m_pParent;
        HANDLE      m_handle;
    };
}

#endif  //_SA_THREAD_PLATFORM_H
