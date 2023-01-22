/*************************************************************
Sakura Game Framework : SaTime.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_TIME_H
#define _SA_TIME_H

#include "SaCore.h"

namespace Sakura
{
    class SaTime
    {
    public:
        static void Initialise();
        static uint32_t GetTimeMilliseconds();
    };
}

#endif  //_SA_TIME_H
