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
    static const uint32_t BUF_SIZE = 1024;
    char buf[BUF_SIZE];
    va_list args;

    va_start(args, pFmt);
    vsprintf_s(buf, BUF_SIZE, pFmt, args);
    va_end(args);

    OutputDebugStringA(buf);
}

void SaBreak()
{
    if (IsDebuggerPresent())
        __debugbreak();
}
