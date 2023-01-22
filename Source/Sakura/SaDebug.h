/*************************************************************
Sakura Game Framework : SaDebug.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_DEBUG_H
#define _SA_DEBUG_H

#include "SaCore.h"

extern void SaPrintf(const char* pFmt, ...);
extern void SaBreak();

inline void SaHook() {};

#define SA_PRINTF SaPrintf
#define SA_BREAK SaBreak

#define SA_ASSERT(condition, fmt, ...)                                                                  \
    if (!(condition))                                                                                   \
    {                                                                                                   \
        SA_PRINTF("SA_ASSERT (%s:%d): [" #condition "] " #fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
        SA_BREAK();                                                                                     \
    }
#define SA_ASSERT_ONCE(condition, fmt, ...)                                                             \
    static bool bDone = false;                                                                          \
    if (!(condition) && !bDone)                                                                         \
    {                                                                                                   \
        bDone = true;                                                                                   \
        SA_PRINTF("SA_ASSERT (%s:%d): [" #condition "] " #fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
        SA_BREAK();                                                                                     \
    }
#define SA_WARNING(condition, fmt, ...)                                                                 \
    if (!(condition))                                                                                   \
    {                                                                                                   \
        SA_PRINTF("SA_WARNING (%s:%d): [" #condition "] " #fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__);    \
    }
#define SA_FAIL(fmt, ...)                                                                               \
    SA_PRINTF("SA_FAIL (%s:%d): " #fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__);                        \
    SA_BREAK();

//Surprising how useful this is for attaching breakpoints to.
#define SA_HOOK SaHook

#endif  //_SA_DEBUG_H
