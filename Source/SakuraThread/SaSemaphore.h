/*************************************************************
Sakura Game Framework : SaSemaphore.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_SEMAPHORE_H
#define _SA_SEMAPHORE_H

#include <Sakura/SaCore.h>
#include PLATFORM_INCLUDE( SA_PLATFORM_DIR/SaSemaphore_Platform.h )

namespace SakuraThread
{
    class SaSemaphore
    {
        friend class SaSemaphore_Platform;

    public:
        SaSemaphore();
        ~SaSemaphore();

        bool Initialise(uint32_t initialCount, uint32_t maxCount);
        void Release();

        bool Wait(uint32_t timeout = 0);
        bool Signal(uint32_t num = 1);

    private:
        SaSemaphore_Platform m_platformSemaphore;

        uint32_t m_initialCount;
        uint32_t m_maxCount;
    };
}

#endif  //_SA_SEMAPHORE_H
