/*************************************************************
Sakura Game Framework : SaCore.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_CORE_H
#error This file should only be included from SaCore.h
#endif

//In true Microsoft fashion, C99 isn't supported and stdint.h 
//isn't shipped with versions of Visual Studio < 2010
#if !defined(_MSC_VER) || _MSC_VER >= 1600
    #include <stdint.h>
#else
    typedef signed __int8       int8_t;
    typedef signed __int16      int16_t;
    typedef signed __int32      int32_t;
    typedef unsigned __int8     uint8_t;
    typedef unsigned __int16    uint16_t;
    typedef unsigned __int32    uint32_t;
    typedef signed __int64      int64_t;
    typedef unsigned __int64    uint64_t;
#endif
