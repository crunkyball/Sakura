/*************************************************************
Sakura Game Framework : SaRand.cpp
Author: Darrell Blake
*************************************************************/

#include "SaRand.h"
#include "SaDebug.h"
#include <cstdlib>

using namespace Sakura;

SaRand::SaRand()
{
    Initialise(0);
}

SaRand::SaRand(uint32_t seed)
{
    Initialise(seed);
}

SaRand::~SaRand()
{
}

void SaRand::Initialise(uint32_t seed)
{
    m_q[0] = seed;
    for (uint32_t i = 1; i < 4096; i++)
        m_q[i] = 1812433253UL * (m_q[i - 1] ^ (m_q[i - 1] >> 30)) + i;

    m_carry = m_q[4095] % 61137367UL;
    m_index = 4095;
}

uint32_t SaRand::Rand_CMWC()
{
    uint64_t t, a = 18782LL;
    uint32_t x, r = 0xfffffffe;
    m_index = (m_index + 1) & 4095;
    t = a * m_q[m_index] + m_carry;
    m_carry = (t >> 32);
    x = static_cast<uint32_t>(t + m_carry);

    if(x < m_carry)
    {
        x++;
        m_carry++;
    }

    return (m_q[m_index] = r - x);
}

uint32_t SaRand::GetUint32()
{
    return Rand_CMWC();
}

uint32_t SaRand::GetUint32(uint32_t max)
{
    return Rand_CMWC() % max;
}

uint32_t SaRand::GetUint32(uint32_t min, uint32_t max)
{
    SA_ASSERT(min < max, "Min less than max.");

    //If min isn't less than max then flip them. Not sure 
    //how else I should deal with this situation.
    if (min < max)
        return min + (Rand_CMWC() % (max - min));
    return max + (Rand_CMWC() % (min - max));
}

float SaRand::GetFloat()
{
    return Rand_CMWC() * (1.0f / 0xFFFFFFFF);
}
