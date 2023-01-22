/*************************************************************
Sakura Game Framework : SaConditionVariable.cpp
Author: Darrell Blake
*************************************************************/

#include "SaConditionVariable.h"

using namespace SakuraThread;

SaConditionVariable::SaConditionVariable()
{
}

void SaConditionVariable::Wait(SaMutex& rMutex)
{
    m_platformConditionVariable.Wait(rMutex.m_platformMutex);
}

void SaConditionVariable::Signal()
{
    m_platformConditionVariable.Signal();
}

void SaConditionVariable::Broadcast()
{
    m_platformConditionVariable.Broadcast();
}
