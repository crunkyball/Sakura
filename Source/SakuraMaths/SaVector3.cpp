/*************************************************************
Sakura Game Framework : SaVector3.cpp
Author: Darrell Blake
*************************************************************/

#include "SaMaths.h"
#include "SaVector3.h"

using namespace SakuraMaths;

const SaVector3 SaVector3::ALL_ZERO(0.0f, 0.0f, 0.0f);
const SaVector3 SaVector3::X_AXIS(1.0f, 0.0f, 0.0f);
const SaVector3 SaVector3::Y_AXIS(0.0f, 1.0f, 0.0f);
const SaVector3 SaVector3::Z_AXIS(0.0f, 0.0f, 1.0f);

SaVector3::SaVector3()
{
}

SaVector3::SaVector3(const float x, const float y, const float z) : m_x(x), m_y(y), m_z(z)
{
}

SaVector3::SaVector3(const SaVector3& rVec) : m_x(rVec.m_x), m_y(rVec.m_y), m_z(rVec.m_z)
{
}

SaVector3::~SaVector3()
{
}

SaVector3& SaVector3::operator =(const SaVector3& rVec)
{
    m_x = rVec.m_x;
    m_y = rVec.m_y;
    m_z = rVec.m_z;
    
    return *this;
}

bool SaVector3::operator ==(const SaVector3& rVec) const
{
    return m_x == rVec.m_x && m_y == rVec.m_y && m_z == rVec.m_z;
}

bool SaVector3::operator !=(const SaVector3& rVec) const
{
    return m_x != rVec.m_x || m_y != rVec.m_y || m_z != rVec.m_z;
}

SaVector3 SaVector3::operator +(const SaVector3& rVec) const
{
    SaVector3 vec;
    vec.m_x = m_x + rVec.m_x;
    vec.m_y = m_y + rVec.m_y;
    vec.m_z = m_z + rVec.m_z;
    
    return vec;
}

SaVector3 SaVector3::operator -(const SaVector3& rVec) const
{
    SaVector3 vec;
    vec.m_x = m_x - rVec.m_x;
    vec.m_y = m_y - rVec.m_y;
    vec.m_z = m_z - rVec.m_z;
    
    return vec;
}

SaVector3 SaVector3::operator *(const float val) const
{
    SaVector3 vec;
    vec.m_x = m_x * val;
    vec.m_y = m_y * val;
    vec.m_z = m_z * val;
    
    return vec;
}

//Dot product.
float SaVector3::operator *(const SaVector3& rVec) const
{
    return (m_x*rVec.m_x) + (m_y*rVec.m_y) + (m_z*rVec.m_z);
}

SaVector3 SaVector3::operator /(const float val) const
{
    SaVector3 vec;
    vec.m_x = m_x / val;
    vec.m_y = m_y / val;
    vec.m_z = m_z / val;
    
    return vec;
}

SaVector3 SaVector3::operator -() const
{
    SaVector3 vec;
    vec.m_x = -m_x;
    vec.m_y = -m_y;
    vec.m_z = -m_z;

    return vec;
}

SaVector3& SaVector3::operator +=(const SaVector3& rVec)
{
    m_x += rVec.m_x;
    m_y += rVec.m_y;
    m_z += rVec.m_z;
    
    return *this;
}

SaVector3& SaVector3::operator -=(const SaVector3& rVec)
{
    m_x -= rVec.m_x;
    m_y -= rVec.m_y;
    m_z -= rVec.m_z;
    
    return *this;
}

SaVector3& SaVector3::operator *=(const float val)
{
    m_x *= val;
    m_y *= val;
    m_z *= val;
    
    return *this;
}

SaVector3& SaVector3::operator /=(const float val)
{
    m_x /= val;
    m_y /= val;
    m_z /= val;
    
    return *this;
}

float SaVector3::Length() const
{
    return sqrt(LengthSquared());
}

float SaVector3::LengthSquared() const
{
    return (m_x*m_x) + (m_y*m_y) + (m_z*m_z);
}

float SaVector3::Normalise()
{
    float fLength = Length();
    m_x /= fLength;
    m_y /= fLength;
    m_z /= fLength;

    return fLength;
}

SaVector3 SaVector3::GetNormalised(float* pLength) const
{
    SaVector3 vec = *this;
    float length = vec.Normalise();
    if (pLength)
        *pLength = length;
    return vec;
}

SaVector3 SaVector3::Cross(const SaVector3& rVec) const
{
    SaVector3 vec;
    vec.m_x = (m_y*rVec.m_z) - (m_z*rVec.m_y);
    vec.m_y = (m_z*rVec.m_x) - (m_x*rVec.m_z);
    vec.m_z = (m_x*rVec.m_y) - (m_y*rVec.m_x);
    
    return vec;
}

void SaVector3::Set(const float x, const float y, const float z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}
