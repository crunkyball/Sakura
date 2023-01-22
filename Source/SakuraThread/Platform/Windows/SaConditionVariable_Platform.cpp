/*************************************************************
Sakura Game Framework : SaConditionVariable_Platform.h
Author: Darrell Blake

Windows platform implementation for SaConditionVariable.
*************************************************************/

#include "SaConditionVariable_Platform.h"

using namespace SakuraThread;

SaConditionVariable_Platform::SaConditionVariable_Platform()
{
    InitializeConditionVariable(&m_variable);
}

void SaConditionVariable_Platform::Wait(SaMutex_Platform& rMutex)
{
    SleepConditionVariableCS(&m_variable, &rMutex.GetCriticalSection(), INFINITE);
}

void SaConditionVariable_Platform::Signal()
{
    WakeConditionVariable(&m_variable);
}

void SaConditionVariable_Platform::Broadcast()
{
    WakeAllConditionVariable(&m_variable);
}
