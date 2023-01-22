/*************************************************************
Sakura Game Framework : SaConditionVariable.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_CONDITION_VARIABLE_H
#define _SA_CONDITION_VARIABLE_H

#include <Sakura/SaCore.h>
#include PLATFORM_INCLUDE( SA_PLATFORM_DIR/SaConditionVariable_Platform.h )
#include "SaMutex.h"

namespace SakuraThread
{
    class SaConditionVariable
    {
    public:
        SaConditionVariable();

        void Wait(SaMutex& rMutex);
        void Signal();
        void Broadcast();

    private:
        SaConditionVariable_Platform    m_platformConditionVariable;
    };
}

#endif  //_SA_CONDITION_VARIABLE_H
