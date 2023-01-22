/*************************************************************
Sakura Game Framework : SaMutex_Platform.cpp
Author: Darrell Blake

Windows platform implementation for SaMutex.
*************************************************************/

#include "SaMutex_Platform.h"
#include <Sakura/SaDebug.h>

using namespace SakuraThread;

SaMutex_Platform::SaMutex_Platform()
{
    InitializeCriticalSection(&m_criticalSection);
}

SaMutex_Platform::~SaMutex_Platform()
{
    DeleteCriticalSection(&m_criticalSection);
}

void SaMutex_Platform::Lock()
{
    EnterCriticalSection(&m_criticalSection);
}

bool SaMutex_Platform::TryLock()
{
    return TryEnterCriticalSection(&m_criticalSection) != 0;
}

void SaMutex_Platform::Unlock()
{
    LeaveCriticalSection(&m_criticalSection);
}

CRITICAL_SECTION& SaMutex_Platform::GetCriticalSection()
{
    return m_criticalSection;
}
