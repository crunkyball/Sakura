/*************************************************************
Sakura Game Framework : SaMatrix33.cpp
Author: Darrell Blake
*************************************************************/

#include "SaMatrix33.h"
#include "SaMaths.h"
#include <Sakura/SaDebug.h>

using namespace SakuraMaths;

const SaMatrix33 SaMatrix33::ALL_ZERO(0.0f, 0.0f, 0.0f,
                                      0.0f, 0.0f, 0.0f,
                                      0.0f, 0.0f, 0.0f);
const SaMatrix33 SaMatrix33::IDENTITY(1.0f, 0.0f, 0.0f,
                                      0.0f, 1.0f, 0.0f,
                                      0.0f, 0.0f, 1.0f);

SaMatrix33::SaMatrix33()
{
}

SaMatrix33::SaMatrix33(float m00, float m01, float m02,
                       float m10, float m11, float m12,
                       float m20, float m21, float m22) :
                       m_column0(m00, m10, m20),
                       m_column1(m01, m11, m21),
                       m_column2(m02, m12, m22)
{
}

SaMatrix33::SaMatrix33(const SaVector3& col0,
                       const SaVector3& col1,
                       const SaVector3& col2) :
                       m_column0(col0),
                       m_column1(col1),
                       m_column2(col2)
{
}

SaMatrix33::SaMatrix33(const SaMatrix33& rMat) : 
                       m_column0(rMat.m_column0),
                       m_column1(rMat.m_column1),
                       m_column2(rMat.m_column2)
{
}
                       
SaMatrix33::~SaMatrix33()
{
}

SaMatrix33& SaMatrix33::operator =(const SaMatrix33& rMat)
{
    m_column0 = rMat.m_column0;
    m_column1 = rMat.m_column1;
    m_column2 = rMat.m_column2;
    
    return *this;
}

bool SaMatrix33::operator ==(const SaMatrix33& rMat) const
{
    return m_column0 == rMat.m_column0 && 
           m_column1 == rMat.m_column1 && 
           m_column2 == rMat.m_column2;
}

bool SaMatrix33::operator !=(const SaMatrix33& rMat) const
{
    return m_column0 != rMat.m_column0 || 
           m_column1 != rMat.m_column1 || 
           m_column2 != rMat.m_column2;
}

SaMatrix33 SaMatrix33::operator +(const SaMatrix33& rMat) const
{
    SaMatrix33 mat;
    mat.m_column0 = m_column0 + rMat.m_column0;
    mat.m_column1 = m_column1 + rMat.m_column1;
    mat.m_column2 = m_column2 + rMat.m_column2;
    
    return mat;
}

SaMatrix33 SaMatrix33::operator -(const SaMatrix33& rMat) const
{
    SaMatrix33 mat;
    mat.m_column0 = m_column0 - rMat.m_column0;
    mat.m_column1 = m_column1 - rMat.m_column1;
    mat.m_column2 = m_column2 - rMat.m_column2;
    
    return mat;
}

SaMatrix33 SaMatrix33::operator *(const float val) const
{
    SaMatrix33 mat;
    mat.m_column0 = m_column0 * val;
    mat.m_column1 = m_column1 * val;
    mat.m_column2 = m_column2 * val;
    
    return mat;
}

SaMatrix33 SaMatrix33::operator *(const SaMatrix33& rMat) const
{
    SaVector3 vRow0 = GetRow0();
    SaVector3 vRow1 = GetRow1();
    SaVector3 vRow2 = GetRow2();
    
    SaMatrix33 mat;
    mat.m_column0 = SaVector3(vRow0*rMat.m_column0, vRow1*rMat.m_column0, vRow2*rMat.m_column0);
    mat.m_column1 = SaVector3(vRow0*rMat.m_column1, vRow1*rMat.m_column1, vRow2*rMat.m_column1);
    mat.m_column2 = SaVector3(vRow0*rMat.m_column2, vRow1*rMat.m_column2, vRow2*rMat.m_column2);
   
    return mat;
}

SaMatrix33 SaMatrix33::operator /(const float val) const
{
    SaMatrix33 mat;
    mat.m_column0 = m_column0 / val;
    mat.m_column1 = m_column1 / val;
    mat.m_column2 = m_column2 / val;
    
    return mat;
}

SaMatrix33& SaMatrix33::operator +=(const SaMatrix33& rMat)
{   
    m_column0 += rMat.m_column0;
    m_column1 += rMat.m_column1;
    m_column2 += rMat.m_column2;
    
    return *this;
}

SaMatrix33& SaMatrix33::operator -=(const SaMatrix33& rMat)
{
    m_column0 -= rMat.m_column0;
    m_column1 -= rMat.m_column1;
    m_column2 -= rMat.m_column2;
    
    return *this;
}

SaMatrix33& SaMatrix33::operator *=(const float val)
{
    m_column0 *= val;
    m_column1 *= val;
    m_column2 *= val;
    
    return *this;
}

SaMatrix33& SaMatrix33::operator *=(const SaMatrix33& rMat)
{  
    SaVector3 vRow0 = GetRow0();
    SaVector3 vRow1 = GetRow1();
    SaVector3 vRow2 = GetRow2();
    
    m_column0 = SaVector3(vRow0*rMat.m_column0, vRow1*rMat.m_column0, vRow2*rMat.m_column0);
    m_column1 = SaVector3(vRow0*rMat.m_column1, vRow1*rMat.m_column1, vRow2*rMat.m_column1);
    m_column2 = SaVector3(vRow0*rMat.m_column2, vRow1*rMat.m_column2, vRow2*rMat.m_column2);
    
    return *this;
}

SaMatrix33& SaMatrix33::operator /=(const float val)
{
    m_column0 /= val;
    m_column1 /= val;
    m_column2 /= val;
    
    return *this;
}

SaVector3 SaMatrix33::operator *(const SaVector3& rVec) const
{
    SaVector3 vRow0 = GetRow0();
    SaVector3 vRow1 = GetRow1();
    SaVector3 vRow2 = GetRow2();
    
    SaVector3 vec;
    vec.m_x = vRow0*rVec;
    vec.m_y = vRow1*rVec;
    vec.m_z = vRow2*rVec;
    
    return vec;
}

SaMatrix33& SaMatrix33::Transpose()
{
    SaMatrix33 mat = *this;
    m_column0 = mat.GetRow0();
    m_column1 = mat.GetRow1();
    m_column2 = mat.GetRow2();
    
    return *this;
}

SaMatrix33 SaMatrix33::GetTransposed() const
{
    SaMatrix33 mat;
    mat.m_column0 = GetRow0();
    mat.m_column1 = GetRow1();
    mat.m_column2 = GetRow2();

    return mat;
}

SaMatrix33& SaMatrix33::Orthonormalise()
{
    m_column0.Normalise();
    m_column1.Normalise();

    m_column2 = m_column0.Cross(m_column1);
    m_column1 = m_column2.Cross(m_column0);

    return *this;
}

SaMatrix33 SaMatrix33::GetOrthonormalised() const
{
    SaMatrix33 mat = *this;
    mat.Orthonormalise();
    return mat;
}

void SaMatrix33::SetToIdentity()
{
    m_column0.Set(1.0f, 0.0f, 0.0f);
    m_column1.Set(0.0f, 1.0f, 0.0f);
    m_column2.Set(0.0f, 0.0f, 1.0f);
}

void SaMatrix33::SetAllZeros()
{
    m_column0.Set(0.0f, 0.0f, 0.0f);
    m_column1.Set(0.0f, 0.0f, 0.0f);
    m_column2.Set(0.0f, 0.0f, 0.0f);
}

//Static utility functions for creating matrices.
SaMatrix33 SaMatrix33::CreateXRotation(const float rad)
{
    float cos = cosf(rad);
    float sin = sinf(rad);

    SaMatrix33 mat;
    mat.SetToIdentity();
    mat.m_column1.Set(0.0f, cos, sin);
    mat.m_column2.Set(0.0f, -sin, cos);

    return mat;
}

SaMatrix33 SaMatrix33::CreateYRotation(const float rad)
{
    float cos = cosf(rad);
    float sin = sinf(rad);

    SaMatrix33 mat;
    mat.SetToIdentity();
    mat.m_column0.Set(cos, 0.0f, -sin);
    mat.m_column2.Set(sin, 0.0f, cos);

    return mat;
}

SaMatrix33 SaMatrix33::CreateZRotation(const float rad)
{
    float cos = cosf(rad);
    float sin = sinf(rad);

    SaMatrix33 mat;
    mat.SetToIdentity();
    mat.m_column0.Set(cos, sin, 0.0f);
    mat.m_column1.Set(-sin, cos, 0.0f);

    return mat;
}

SaMatrix33 SaMatrix33::CreateRotation(const SaVector3& rAxis, const float rad)
{
    SA_ASSERT(rAxis.Length() > 0.99f && rAxis.Length() < 1.01, "Has to be a unit vector.");

    float x = rAxis.GetX();
    float y = rAxis.GetY();
    float z = rAxis.GetZ();

    float cos = cosf(rad);
    float sin = sinf(rad);
    float ver = 1.0f-cos;

    SaMatrix33 mat;

    mat.m_column0.Set(ver*x*x + cos, ver*x*y + sin*z, ver*x*z - sin*y);
    mat.m_column1.Set(ver*x*y - sin*z, ver*y*y + cos, ver*y*z + sin*x);
    mat.m_column2.Set(ver*x*y + sin*y, ver*y*z - sin*x, ver*z*z + cos);

    return mat;
}

SaMatrix33 SaMatrix33::CreateRotation(const float pitch, const float yaw,  const float roll)
{
    if (pitch == 0.0f && yaw == 0.0f && roll == 0.0f)
    {
        return SaMatrix33::IDENTITY;
    }

    //Calculate the arbitrary axis to rotate around and pass into the above function.
    SaVector3 xAxis = SaVector3::X_AXIS * pitch;
    SaVector3 yAxis = SaVector3::Y_AXIS * yaw;
    SaVector3 zAxis = SaVector3::Z_AXIS * roll;

    SaVector3 arbAxis = xAxis + yAxis + zAxis;
    float rad = arbAxis.Normalise();

    return CreateRotation(arbAxis, rad);
}

SaMatrix33 SaMatrix33::CreateScale(const float x, const float y, const float z)
{
    SaMatrix33 mat;
    mat.m_column0.Set(x, 0.0f, 0.0f);
    mat.m_column1.Set(0.0f, y, 0.0f);
    mat.m_column2.Set(0.0f, 0.0f, z);

    return mat;
}

SaMatrix33 SaMatrix33::CreateScaleUniform(const float scale)
{
    return CreateScale(scale, scale, scale);
}
