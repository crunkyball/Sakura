/*************************************************************
Sakura Game Framework : SaMutex.cpp
Author: Darrell Blake
*************************************************************/

#include "SaMutex.h"

using namespace SakuraThread;

SaMutex::SaMutex()
{
}

SaMutex::~SaMutex()
{
}

void SaMutex::Lock()
{
    m_platformMutex.Lock();
}

bool SaMutex::TryLock()
{
    return m_platformMutex.TryLock();
}

void SaMutex::Unlock()
{
    m_platformMutex.Unlock();
}
