/*************************************************************
Sakura Game Framework : SaDebug_Platform.cpp
Author: Darrell Blake

Windows platform implementation for SaDebug.
*************************************************************/

#include <cstdarg>
#include <cstdio>
#include "../../SaDebug.h"
#include <Windows.h>

void SaPrintf(const char* pFmt, ...)
{
    char buf[1024];
    va_list args;

    va_start(args, pFmt);
    vsprintf(buf, pFmt, args);
    va_end(args);

    OutputDebugStringA(buf);
}

void SaBreak()
{
    if (IsDebuggerPresent())
        __debugbreak();
}
