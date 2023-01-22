/*************************************************************
Sakura Game Framework : SaTime_Platform.cpp
Author: Darrell Blake

Windows platform implementation for SaTime.
*************************************************************/

#include "../../SaTime.h"
#include <Windows.h>

using namespace Sakura;

static LARGE_INTEGER startTime;
static LARGE_INTEGER frequency;

void SaTime::Initialise()
{
    QueryPerformanceCounter(&startTime);
    QueryPerformanceFrequency(&frequency);
}

uint32_t SaTime::GetTimeMilliseconds()
{
    LARGE_INTEGER timeNow;
    QueryPerformanceCounter(&timeNow);

    LARGE_INTEGER elapsed;
    elapsed.QuadPart = timeNow.QuadPart - startTime.QuadPart;

    //elapsed.QuadPart *= 1000000;  //Microseconds.
    elapsed.QuadPart *= 1000;       //Milliseconds.

    return static_cast<uint32_t>(elapsed.QuadPart / frequency.QuadPart);
}
