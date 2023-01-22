/*************************************************************
Sakura Game Framework : SaCore.h
Author: Darrell Blake

This should be included from every header file. It contains 
the type definitions as well as any useful framework 
defines/macros etc.
*************************************************************/

#ifndef _SA_CORE_H
#define _SA_CORE_H

#include "SaTypes.h"

#define NULL 0

#define STRINGIFY( X ) #X
#define PLATFORM_INCLUDE( X ) STRINGIFY( X )

//Compile time meta-programming function to count the 
//number of bits required for a given value.
template <uint32_t val, bool recurse = false>
struct NUM_BITS
{
    static const uint32_t Value = NUM_BITS<(val >> 1)>::Value + 1;
};

template <>
struct NUM_BITS<0, false>
{
    static const uint32_t Value = 1;
};

template <>
struct NUM_BITS<0, true>
{
    static const uint32_t Value = 0;
};

#endif  //_SA_CORE_H
