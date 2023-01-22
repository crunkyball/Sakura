/*************************************************************
Sakura Game Framework : SaConditionVariable_Platform.h
Author: Darrell Blake

Windows platform implementation for SaConditionVariable.

Condition variables are only supported in >= Windows 7. If by 
some bizarre twist of fate this has to work on earlier versions 
of Windows it will have to be changed. Perhaps to a single 
count semaphore. That would be a kernel level lock so would 
be slower than this.
*************************************************************/

#ifndef _SA_CONDITION_VARIABLE_PLATFORM_H
#define _SA_CONDITION_VARIABLE_PLATFORM_H

#include <Sakura/SaCore.h>
#include <Windows.h>
#include "SaMutex_Platform.h"

namespace SakuraThread
{
    class SaConditionVariable_Platform
    {
    public:
        SaConditionVariable_Platform();

        void Wait(SaMutex_Platform& rMutex);
        void Signal();
        void Broadcast();

    private:
        CONDITION_VARIABLE  m_variable;
    };
}

#endif  //_SA_CONDITION_VARIABLE_PLATFORM_H
