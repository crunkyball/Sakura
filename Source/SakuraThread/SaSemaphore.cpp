/*************************************************************
Sakura Game Framework : SaSemaphore.cpp
Author: Darrell Blake
*************************************************************/

#include "SaSemaphore.h"

using namespace SakuraThread;

SaSemaphore::SaSemaphore() : 
    m_platformSemaphore(this)
{
}

SaSemaphore::~SaSemaphore()
{
}

bool SaSemaphore::Initialise(uint32_t initialCount, uint32_t maxCount)
{
    m_initialCount = initialCount;
    m_maxCount = maxCount;

    return m_platformSemaphore.Initialise();
}

void SaSemaphore::Release()
{
    m_platformSemaphore.Release();
}

bool SaSemaphore::Wait(uint32_t timeout)
{
    return m_platformSemaphore.Wait(timeout);
}

bool SaSemaphore::Signal(uint32_t num)
{
    return m_platformSemaphore.Signal(num);
}
