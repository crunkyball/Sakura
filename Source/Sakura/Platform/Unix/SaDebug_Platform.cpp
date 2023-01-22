/*************************************************************
Sakura Game Framework : SaDebug_Platform.cpp
Author: Darrell Blake

Unix platform implementation for SaDebug.
*************************************************************/

#include <cstdarg>
#include <cstdio>
#include "../../SaDebug.h"
#include <cassert>

void SaPrintf(const char* pFmt, ...)
{
    char buf[1024];
    va_list args;

    va_start(args, pFmt);
    vsprintf(buf, pFmt, args);
    va_end(args);

    printf(buf);
}

void SaBreak()
{
    assert(0);  //This will do for now.
}
