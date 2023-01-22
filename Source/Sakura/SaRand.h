/*************************************************************
Sakura Game Framework : SaRand.h
Author: Darrell Blake

Instead of Mersenne Twister I've opted for George Marsaglia's 
Complementary Multiply-with-Carry algorithm CMWC4096.
*************************************************************/

#ifndef _SA_RAND_H
#define _SA_RAND_H

#include "SaCore.h"

namespace Sakura
{
    class SaRand
    {
    public:
        SaRand();
        SaRand(uint32_t seed);
        ~SaRand();

        void Initialise(uint32_t seed);

        uint32_t GetUint32();

        //These functions are exclusive.
        uint32_t GetUint32(uint32_t max);
        uint32_t GetUint32(uint32_t min, uint32_t max);

        //Returns a float between 0 and 1.
        float GetFloat();

    private:
        uint32_t Rand_CMWC();

        uint32_t m_carry;
        uint32_t m_index;
        uint32_t m_q[4096];
    };
}

#endif  //_SA_RAND_H
