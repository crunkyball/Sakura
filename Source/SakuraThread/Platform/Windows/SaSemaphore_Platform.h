/*************************************************************
Sakura Game Framework : SaSemaphore_Platform.h
Author: Darrell Blake

Windows platform implementation for SaSemaphore.
*************************************************************/

#ifndef _SA_SEMAPHORE_PLATFORM_H
#define _SA_SEMAPHORE_PLATFORM_H

#include <Sakura/SaCore.h>
#include <Windows.h>

namespace SakuraThread
{
    class SaSemaphore;

    class SaSemaphore_Platform
    {
    public:
        SaSemaphore_Platform(SaSemaphore* pParent);
        ~SaSemaphore_Platform();

        bool Initialise();
        void Release();

        bool Wait(uint32_t timeout);
        bool Signal(uint32_t num);

    private:
        SaSemaphore*    m_pParent;
        HANDLE          m_handle;
    };
}

#endif  //_SA_SEMAPHORE_PLATFORM_H
