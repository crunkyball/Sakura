/*************************************************************
Sakura Game Framework : SaVector4.cpp
Author: Darrell Blake
*************************************************************/

#include "SaMaths.h"
#include "SaVector4.h"

using namespace SakuraMaths;

const SaVector4 SaVector4::ALL_ZERO(0.0f, 0.0f, 0.0f, 0.0f);
const SaVector4 SaVector4::X_AXIS(1.0f, 0.0f, 0.0f, 0.0f);
const SaVector4 SaVector4::Y_AXIS(0.0f, 1.0f, 0.0f, 0.0f);
const SaVector4 SaVector4::Z_AXIS(0.0f, 0.0f, 1.0f, 0.0f);
const SaVector4 SaVector4::W_AXIS(0.0f, 0.0f, 0.0f, 1.0f);

SaVector4::SaVector4()
{
}

SaVector4::SaVector4(const float x, const float y, const float z, const float w) : m_x(x), m_y(y), m_z(z), m_w(w)
{
}

SaVector4::SaVector4(const SaVector3& rVec, const float w) : m_x(rVec.m_x), m_y(rVec.m_y), m_z(rVec.m_z), m_w(w)
{
}

SaVector4::SaVector4(const SaVector4& rVec) : m_x(rVec.m_x), m_y(rVec.m_y), m_z(rVec.m_z), m_w(rVec.m_w)
{
}

SaVector4::~SaVector4()
{
}

SaVector4& SaVector4::operator =(const SaVector4& rVec)
{
    m_x = rVec.m_x;
    m_y = rVec.m_y;
    m_z = rVec.m_z;
    m_w = rVec.m_w;
    
    return *this;
}

bool SaVector4::operator ==(const SaVector4& rVec) const
{
    return m_x == rVec.m_x && m_y == rVec.m_y && m_z == rVec.m_z && m_w == rVec.m_w;
}

bool SaVector4::operator !=(const SaVector4& rVec) const
{
    return m_x != rVec.m_x || m_y != rVec.m_y || m_z != rVec.m_z || m_w != rVec.m_w;
}

SaVector4 SaVector4::operator +(const SaVector4& rVec) const
{
    SaVector4 vec;
    vec.m_x = m_x + rVec.m_x;
    vec.m_y = m_y + rVec.m_y;
    vec.m_z = m_z + rVec.m_z;
    vec.m_w = m_w + rVec.m_w;
    
    return vec;
}

SaVector4 SaVector4::operator -(const SaVector4& rVec) const
{
    SaVector4 vec;
    vec.m_x = m_x - rVec.m_x;
    vec.m_y = m_y - rVec.m_y;
    vec.m_z = m_z - rVec.m_z;
    vec.m_w = m_w - rVec.m_w;
    
    return vec;
}

SaVector4 SaVector4::operator *(const float val) const
{
    SaVector4 vec;
    vec.m_x = m_x * val;
    vec.m_y = m_y * val;
    vec.m_z = m_z * val;
    vec.m_w = m_w * val;
    
    return vec;
}

//Dot product.
float SaVector4::operator *(const SaVector4& rVec) const
{
    return (m_x*rVec.m_x) + (m_y*rVec.m_y) + (m_z*rVec.m_z) + (m_w*rVec.m_w);
}

SaVector4 SaVector4::operator /(const float val) const
{
    SaVector4 vec;
    vec.m_x = m_x / val;
    vec.m_y = m_y / val;
    vec.m_z = m_z / val;
    vec.m_w = m_w / val;
    
    return vec;
}

SaVector4 SaVector4::operator -() const
{
    SaVector4 vec;
    vec.m_x = -m_x;
    vec.m_y = -m_y;
    vec.m_z = -m_z;
    vec.m_w = -m_w;

    return vec;
}

SaVector4& SaVector4::operator +=(const SaVector4& rVec)
{
    m_x += rVec.m_x;
    m_y += rVec.m_y;
    m_z += rVec.m_z;
    m_w += rVec.m_w;
    
    return *this;
}

SaVector4& SaVector4::operator -=(const SaVector4& rVec)
{
    m_x -= rVec.m_x;
    m_y -= rVec.m_y;
    m_z -= rVec.m_z;
    m_w -= rVec.m_w;
    
    return *this;
}

SaVector4& SaVector4::operator *=(const float val)
{
    m_x *= val;
    m_y *= val;
    m_z *= val;
    m_w *= val;
    
    return *this;
}

SaVector4& SaVector4::operator /=(const float val)
{
    m_x /= val;
    m_y /= val;
    m_z /= val;
    m_w /= val;
    
    return *this;
}

float SaVector4::Length() const
{
    return sqrt(LengthSquared());
}

float SaVector4::LengthSquared() const
{
    return (m_x*m_x) + (m_y*m_y) + (m_z*m_z) + (m_w*m_w);
}

float SaVector4::Normalise()
{
    float fLength = Length();
    m_x /= fLength;
    m_y /= fLength;
    m_z /= fLength;
    m_w /= fLength;

    return fLength;
}

SaVector4 SaVector4::GetNormalised(float* pLength) const
{
    SaVector4 vec = *this;
    float length = vec.Normalise();
    if (pLength)
        *pLength = length;
    return vec;
}

SaVector4 SaVector4::Cross(const SaVector4& rVec) const
{
    SaVector4 vec;
    vec.m_x = (m_y*rVec.m_z) - (m_z*rVec.m_y);
    vec.m_y = (m_z*rVec.m_x) - (m_x*rVec.m_z);
    vec.m_z = (m_x*rVec.m_y) - (m_y*rVec.m_x);
    vec.m_w = 0.0f;
    
    return vec;
}

void SaVector4::Set(const float x, const float y, const float z, const float w)
{
    m_x = x;
    m_y = y;
    m_z = z;
    m_w = w;
}
