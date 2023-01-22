/*************************************************************
Sakura Game Framework : SaColour.cpp
Author: Darrell Blake
*************************************************************/

#include "SaColour.h"

using namespace Sakura;

const SaColour SaColour::BLACK(0.0f, 0.0f, 0.0f, 1.0f);
const SaColour SaColour::WHITE(1.0f, 1.0f, 1.0f, 1.0f);
const SaColour SaColour::RED(1.0f, 0.0f, 0.0f, 1.0f);
const SaColour SaColour::GREEN(0.0f, 1.0f, 0.0f, 1.0f);
const SaColour SaColour::BLUE(0.0f, 0.0f, 1.0f, 1.0f);
const SaColour SaColour::YELLOW(1.0f, 1.0f, 0.0f, 1.0f);
const SaColour SaColour::MAGENTA(1.0f, 0.0f, 1.0f, 1.0f);
const SaColour SaColour::CYAN(0.0f, 1.0f, 1.0f, 1.0f);
const SaColour SaColour::SAKURA(0.76f, 0.51f, 0.62f, 1.0f);

SaColour::SaColour() :
    m_fR(0.0f),
    m_fG(0.0f),
    m_fB(0.0f),
    m_fA(1.0f)
{
}

SaColour::SaColour(float fR, float fG, float fB, float fA) :
    m_fR(fR),
    m_fG(fG),
    m_fB(fB),
    m_fA(fA)
{
}

SaColour& SaColour::operator =(const SaColour& rColour)
{
    m_fR = rColour.m_fR;
    m_fG = rColour.m_fG;
    m_fB = rColour.m_fB;
    m_fA = rColour.m_fA;

    return *this;
}

bool SaColour::operator ==(const SaColour& rColour) const
{
    return m_fR == rColour.m_fR && m_fG == rColour.m_fG && m_fB == rColour.m_fB && m_fA == rColour.m_fA;
}

bool SaColour::operator !=(const SaColour& rColour) const
{
    return m_fR != rColour.m_fR || m_fG != rColour.m_fG || m_fB != rColour.m_fB || m_fA != rColour.m_fA;
}

void SaColour::Set(const float fR, const float fG, const float fB, const float fA)
{
    m_fR = fR;
    m_fG = fG;
    m_fB = fB;
    m_fA = fA;
}
