/*************************************************************
Sakura Game Framework : SaVector2.cpp
Author: Darrell Blake
*************************************************************/

#include "SaMaths.h"
#include "SaVector2.h"

using namespace SakuraMaths;

const SaVector2 SaVector2::ALL_ZERO(0.0f, 0.0f);
const SaVector2 SaVector2::ALL_ONE(1.0f, 1.0f);
const SaVector2 SaVector2::X_AXIS(1.0f, 0.0f);
const SaVector2 SaVector2::Y_AXIS(0.0f, 1.0f);

SaVector2::SaVector2()
{
}

SaVector2::SaVector2(const float x, const float y) : m_x(x), m_y(y)
{
}

SaVector2::SaVector2(const SaVector2& rVec) : m_x(rVec.m_x), m_y(rVec.m_y)
{
}

SaVector2::~SaVector2()
{
}

SaVector2& SaVector2::operator =(const SaVector2& rVec)
{
    m_x = rVec.m_x;
    m_y = rVec.m_y;
    
    return *this;
}

bool SaVector2::operator ==(const SaVector2& rVec) const
{
    return m_x == rVec.m_x && m_y == rVec.m_y;
}

bool SaVector2::operator !=(const SaVector2& rVec) const
{
    return m_x != rVec.m_x || m_y != rVec.m_y;
}

SaVector2 SaVector2::operator +(const SaVector2& rVec) const
{
    SaVector2 vec;
    vec.m_x = m_x + rVec.m_x;
    vec.m_y = m_y + rVec.m_y;
    
    return vec;
}

SaVector2 SaVector2::operator -(const SaVector2& rVec) const
{
    SaVector2 vec;
    vec.m_x = m_x - rVec.m_x;
    vec.m_y = m_y - rVec.m_y;
    
    return vec;
}

SaVector2 SaVector2::operator *(const float val) const
{
    SaVector2 vec;
    vec.m_x = m_x * val;
    vec.m_y = m_y * val;
    
    return vec;
}

//Dot product.
float SaVector2::operator *(const SaVector2& rVec) const
{
    return (m_x*rVec.m_x) + (m_y*rVec.m_y);
}

SaVector2 SaVector2::operator /(const float val) const
{
    SaVector2 vec;
    vec.m_x = m_x / val;
    vec.m_y = m_y / val;
    
    return vec;
}

SaVector2& SaVector2::operator +=(const SaVector2& rVec)
{
    m_x += rVec.m_x;
    m_y += rVec.m_y;
    
    return *this;
}

SaVector2& SaVector2::operator -=(const SaVector2& rVec)
{
    m_x -= rVec.m_x;
    m_y -= rVec.m_y;
    
    return *this;
}

SaVector2& SaVector2::operator *=(const float val)
{
    m_x *= val;
    m_y *= val;
    
    return *this;
}

SaVector2& SaVector2::operator /=(const float val)
{
    m_x /= val;
    m_y /= val;
    
    return *this;
}

float SaVector2::Length() const
{
    return sqrt(LengthSquared());
}

float SaVector2::LengthSquared() const
{
    return (m_x*m_x) + (m_y*m_y);
}

float SaVector2::Normalise()
{
    float fLength = Length();
    m_x /= fLength;
    m_y /= fLength;

    return fLength;
}

SaVector2 SaVector2::GetNormalised(float* pLength) const
{
    SaVector2 vec = *this;
    float length = vec.Normalise();
    if (pLength)
        *pLength = length;
    return vec;
}

void SaVector2::Set(const float x, const float y)
{
    m_x = x;
    m_y = y;
}
