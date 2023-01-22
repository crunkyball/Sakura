/*************************************************************
Sakura Game Framework : SaTime_Platform.cpp
Author: Darrell Blake

Unix platform implementation for SaTime.
*************************************************************/

#include "SaTime.h"
#include <sys/time.h>

using namespace Sakura;

static timeval SaTime::ms_timeStart;

void SaTime::Initialise()
{
    gettimeofday(&ms_timeStart, NULL);
}

//This probably isn't high enough resolution.
uint32_t SaTime::GetTimeMilliseconds()
{
    timeval now;
    gettimeofday(&now, NULL);
    return (now.tv_sec - ms_timeStart.tv_sec) * 1000 + (now.tv_usec - ms_timeStart.tv_usec) / 1000;
}
