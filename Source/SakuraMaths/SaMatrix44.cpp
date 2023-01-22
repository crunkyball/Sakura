/*************************************************************
Sakura Game Framework : SaMatrix44.cpp
Author: Darrell Blake
*************************************************************/

#include "SaMatrix44.h"
#include "SaMaths.h"
#include <Sakura/SaDebug.h>

using namespace SakuraMaths;

const SaMatrix44 SaMatrix44::ALL_ZERO(0.0f, 0.0f, 0.0f, 0.0f,
                                      0.0f, 0.0f, 0.0f, 0.0f,
                                      0.0f, 0.0f, 0.0f, 0.0f,
                                      0.0f, 0.0f, 0.0f, 0.0f);
const SaMatrix44 SaMatrix44::IDENTITY(1.0f, 0.0f, 0.0f, 0.0f,
                                      0.0f, 1.0f, 0.0f, 0.0f,
                                      0.0f, 0.0f, 1.0f, 0.0f,
                                      0.0f, 0.0f, 0.0f, 1.0f);

SaMatrix44::SaMatrix44()
{
}

SaMatrix44::SaMatrix44(float m00, float m01, float m02, float m03,
                       float m10, float m11, float m12, float m13,
                       float m20, float m21, float m22, float m23,
                       float m30, float m31, float m32, float m33) :
                       m_column0(m00, m10, m20, m30),
                       m_column1(m01, m11, m21, m31),
                       m_column2(m02, m12, m22, m32),
                       m_column3(m03, m13, m23, m33)
{
}

SaMatrix44::SaMatrix44(const SaVector4& col0,
                       const SaVector4& col1,
                       const SaVector4& col2,
                       const SaVector4& col3) :
                       m_column0(col0),
                       m_column1(col1),
                       m_column2(col2),
                       m_column3(col3)
{
}

SaMatrix44::SaMatrix44(const SaMatrix44& rMat) : 
                       m_column0(rMat.m_column0),
                       m_column1(rMat.m_column1),
                       m_column2(rMat.m_column2),
                       m_column3(rMat.m_column3)
{
}
                       
SaMatrix44::~SaMatrix44()
{
}

SaMatrix44& SaMatrix44::operator =(const SaMatrix44& rMat)
{
    m_column0 = rMat.m_column0;
    m_column1 = rMat.m_column1;
    m_column2 = rMat.m_column2;
    m_column3 = rMat.m_column3;
    
    return *this;
}

bool SaMatrix44::operator ==(const SaMatrix44& rMat) const
{
    return m_column0 == rMat.m_column0 && 
           m_column1 == rMat.m_column1 && 
           m_column2 == rMat.m_column2 && 
           m_column3 == rMat.m_column3;
}

bool SaMatrix44::operator !=(const SaMatrix44& rMat) const
{
    return m_column0 != rMat.m_column0 || 
           m_column1 != rMat.m_column1 || 
           m_column2 != rMat.m_column2 || 
           m_column3 != rMat.m_column3;
}

SaMatrix44 SaMatrix44::operator +(const SaMatrix44& rMat) const
{
    SaMatrix44 mat;
    mat.m_column0 = m_column0 + rMat.m_column0;
    mat.m_column1 = m_column1 + rMat.m_column1;
    mat.m_column2 = m_column2 + rMat.m_column2;
    mat.m_column3 = m_column3 + rMat.m_column3;
    
    return mat;
}

SaMatrix44 SaMatrix44::operator -(const SaMatrix44& rMat) const
{
    SaMatrix44 mat;
    mat.m_column0 = m_column0 - rMat.m_column0;
    mat.m_column1 = m_column1 - rMat.m_column1;
    mat.m_column2 = m_column2 - rMat.m_column2;
    mat.m_column3 = m_column3 - rMat.m_column3;
    
    return mat;
}

SaMatrix44 SaMatrix44::operator *(const float val) const
{
    SaMatrix44 mat;
    mat.m_column0 = m_column0 * val;
    mat.m_column1 = m_column1 * val;
    mat.m_column2 = m_column2 * val;
    mat.m_column3 = m_column3 * val;
    
    return mat;
}

SaMatrix44 SaMatrix44::operator *(const SaMatrix44& rMat) const
{
    SaVector4 vRow0 = GetRow0();
    SaVector4 vRow1 = GetRow1();
    SaVector4 vRow2 = GetRow2();
    SaVector4 vRow3 = GetRow3();
    
    SaMatrix44 mat;
    mat.m_column0 = SaVector4(vRow0*rMat.m_column0, vRow1*rMat.m_column0, vRow2*rMat.m_column0, vRow3*rMat.m_column0);
    mat.m_column1 = SaVector4(vRow0*rMat.m_column1, vRow1*rMat.m_column1, vRow2*rMat.m_column1, vRow3*rMat.m_column1);
    mat.m_column2 = SaVector4(vRow0*rMat.m_column2, vRow1*rMat.m_column2, vRow2*rMat.m_column2, vRow3*rMat.m_column2);
    mat.m_column3 = SaVector4(vRow0*rMat.m_column3, vRow1*rMat.m_column3, vRow2*rMat.m_column3, vRow3*rMat.m_column3);
   
    return mat;
}

SaMatrix44 SaMatrix44::operator /(const float val) const
{
    SaMatrix44 mat;
    mat.m_column0 = m_column0 / val;
    mat.m_column1 = m_column1 / val;
    mat.m_column2 = m_column2 / val;
    mat.m_column3 = m_column3 / val;
    
    return mat;
}

SaMatrix44& SaMatrix44::operator +=(const SaMatrix44& rMat)
{   
    m_column0 += rMat.m_column0;
    m_column1 += rMat.m_column1;
    m_column2 += rMat.m_column2;
    m_column3 += rMat.m_column3;
    
    return *this;
}

SaMatrix44& SaMatrix44::operator -=(const SaMatrix44& rMat)
{
    m_column0 -= rMat.m_column0;
    m_column1 -= rMat.m_column1;
    m_column2 -= rMat.m_column2;
    m_column3 -= rMat.m_column3;
    
    return *this;
}

SaMatrix44& SaMatrix44::operator *=(const float val)
{
    m_column0 *= val;
    m_column1 *= val;
    m_column2 *= val;
    m_column3 *= val;
    
    return *this;
}

SaMatrix44& SaMatrix44::operator *=(const SaMatrix44& rMat)
{  
    SaVector4 vRow0 = GetRow0();
    SaVector4 vRow1 = GetRow1();
    SaVector4 vRow2 = GetRow2();
    SaVector4 vRow3 = GetRow3();
    
    m_column0 = SaVector4(vRow0*rMat.m_column0, vRow1*rMat.m_column0, vRow2*rMat.m_column0, vRow3*rMat.m_column0);
    m_column1 = SaVector4(vRow0*rMat.m_column1, vRow1*rMat.m_column1, vRow2*rMat.m_column1, vRow3*rMat.m_column1);
    m_column2 = SaVector4(vRow0*rMat.m_column2, vRow1*rMat.m_column2, vRow2*rMat.m_column2, vRow3*rMat.m_column2);
    m_column3 = SaVector4(vRow0*rMat.m_column3, vRow1*rMat.m_column3, vRow2*rMat.m_column3, vRow3*rMat.m_column3);
    
    return *this;
}

SaMatrix44& SaMatrix44::operator /=(const float val)
{
    m_column0 /= val;
    m_column1 /= val;
    m_column2 /= val;
    m_column3 /= val;
    
    return *this;
}


SaVector4 SaMatrix44::operator *(const SaVector4& rVec) const
{
    SaVector4 vRow0 = GetRow0();
    SaVector4 vRow1 = GetRow1();
    SaVector4 vRow2 = GetRow2();
    SaVector4 vRow3 = GetRow3();
    
    SaVector4 vec;
    vec.m_x = vRow0*rVec;
    vec.m_y = vRow1*rVec;
    vec.m_z = vRow2*rVec;
    vec.m_w = vRow3*rVec;
    
    return vec;
}

SaMatrix44& SaMatrix44::Transpose()
{
    SaMatrix44 mat = *this;
    m_column0 = mat.GetRow0();
    m_column1 = mat.GetRow1();
    m_column2 = mat.GetRow2();
    m_column3 = mat.GetRow3();

    return *this;
}

SaMatrix44 SaMatrix44::GetTransposed() const
{
    SaMatrix44 mat;
    mat.m_column0 = GetRow0();
    mat.m_column1 = GetRow1();
    mat.m_column2 = GetRow2();
    mat.m_column3 = GetRow3();

    return mat;
}

bool SaMatrix44::GetInverse(SaMatrix44& rOutMatrix)
{
    SaVector4 column0 = SaVector4(m_column1.GetY()*m_column2.GetZ()*m_column3.GetW() - m_column1.GetY()*m_column2.GetW()*m_column3.GetZ() - m_column2.GetY()*m_column1.GetZ()*m_column3.GetW() + m_column2.GetY()*m_column1.GetW()*m_column3.GetZ() + m_column3.GetY()*m_column1.GetZ()*m_column2.GetW() - m_column3.GetY()*m_column1.GetW()*m_column2.GetZ(),
                                  -m_column0.GetY()*m_column2.GetZ()*m_column3.GetW() + m_column0.GetY()*m_column2.GetW()*m_column3.GetZ() + m_column2.GetY()*m_column0.GetZ()*m_column3.GetW() - m_column2.GetY()*m_column0.GetW()*m_column3.GetZ() - m_column3.GetY()*m_column0.GetZ()*m_column2.GetW() + m_column3.GetY()*m_column0.GetW()*m_column2.GetZ(),
                                  m_column0.GetY()*m_column1.GetZ()*m_column3.GetW() - m_column0.GetY()*m_column1.GetW()*m_column3.GetZ() - m_column1.GetY()*m_column0.GetZ()*m_column3.GetW() + m_column1.GetY()*m_column0.GetW()*m_column3.GetZ() + m_column3.GetY()*m_column0.GetZ()*m_column1.GetW() - m_column3.GetY()*m_column0.GetW()*m_column1.GetZ(),
                                  -m_column0.GetY()*m_column1.GetZ()*m_column2.GetW() + m_column0.GetY()*m_column1.GetW()*m_column2.GetZ() + m_column1.GetY()*m_column0.GetZ()*m_column2.GetW() - m_column1.GetY()*m_column0.GetW()*m_column2.GetZ() - m_column2.GetY()*m_column0.GetZ()*m_column1.GetW() + m_column2.GetY()*m_column0.GetW()*m_column1.GetZ());
    SaVector4 column1 = SaVector4(-m_column1.GetX()*m_column2.GetZ()*m_column3.GetW() + m_column1.GetX()*m_column2.GetW()*m_column3.GetZ() + m_column2.GetX()*m_column1.GetZ()*m_column3.GetW() - m_column2.GetX()*m_column1.GetW()*m_column3.GetZ() - m_column3.GetX()*m_column1.GetZ()*m_column2.GetW() + m_column3.GetX()*m_column1.GetW()*m_column2.GetZ(),
                                  m_column0.GetX()*m_column2.GetZ()*m_column3.GetW() - m_column0.GetX()*m_column2.GetW()*m_column3.GetZ() - m_column2.GetX()*m_column0.GetZ()*m_column3.GetW() + m_column2.GetX()*m_column0.GetW()*m_column3.GetZ() + m_column3.GetX()*m_column0.GetZ()*m_column2.GetW() - m_column3.GetX()*m_column0.GetW()*m_column2.GetZ(),
                                  -m_column0.GetX()*m_column1.GetZ()*m_column3.GetW() + m_column0.GetX()*m_column1.GetW()*m_column3.GetZ() + m_column1.GetX()*m_column0.GetZ()*m_column3.GetW() - m_column1.GetX()*m_column0.GetW()*m_column3.GetZ() - m_column3.GetX()*m_column0.GetZ()*m_column1.GetW() + m_column3.GetX()*m_column0.GetW()*m_column1.GetZ(),
                                  m_column0.GetX()*m_column1.GetZ()*m_column2.GetW() - m_column0.GetX()*m_column1.GetW()*m_column2.GetZ() - m_column1.GetX()*m_column0.GetZ()*m_column2.GetW() + m_column1.GetX()*m_column0.GetW()*m_column2.GetZ() + m_column2.GetX()*m_column0.GetZ()*m_column1.GetW() - m_column2.GetX()*m_column0.GetW()*m_column1.GetZ());
    SaVector4 column2 = SaVector4(m_column1.GetX()*m_column2.GetY()*m_column3.GetW() - m_column1.GetX()*m_column2.GetW()*m_column3.GetY() - m_column2.GetX()*m_column1.GetY()*m_column3.GetW() + m_column2.GetX()*m_column1.GetW()*m_column3.GetY() + m_column3.GetX()*m_column1.GetY()*m_column2.GetW() - m_column3.GetX()*m_column1.GetW()*m_column2.GetY(),
                                  -m_column0.GetX()*m_column2.GetY()*m_column3.GetW() + m_column0.GetX()*m_column2.GetW()*m_column3.GetY() + m_column2.GetX()*m_column0.GetY()*m_column3.GetW() - m_column2.GetX()*m_column0.GetW()*m_column3.GetY() - m_column3.GetX()*m_column0.GetY()*m_column2.GetW() + m_column3.GetX()*m_column0.GetW()*m_column2.GetY(),
                                  m_column0.GetX()*m_column1.GetY()*m_column3.GetW() - m_column0.GetX()*m_column1.GetW()*m_column3.GetY() - m_column1.GetX()*m_column0.GetY()*m_column3.GetW() + m_column1.GetX()*m_column0.GetW()*m_column3.GetY() + m_column3.GetX()*m_column0.GetY()*m_column1.GetW() - m_column3.GetX()*m_column0.GetW()*m_column1.GetY(),
                                  -m_column0.GetX()*m_column1.GetY()*m_column2.GetW() + m_column0.GetX()*m_column1.GetW()*m_column2.GetY() + m_column1.GetX()*m_column0.GetY()*m_column2.GetW() - m_column1.GetX()*m_column0.GetW()*m_column2.GetY() - m_column2.GetX()*m_column0.GetY()*m_column1.GetW() + m_column2.GetX()*m_column0.GetW()*m_column1.GetY());
    SaVector4 column3 = SaVector4(-m_column1.GetX()*m_column2.GetY()*m_column3.GetZ() + m_column1.GetX()*m_column2.GetZ()*m_column3.GetY() + m_column2.GetX()*m_column1.GetY()*m_column3.GetZ() - m_column2.GetX()*m_column1.GetZ()*m_column3.GetY() - m_column3.GetX()*m_column1.GetY()*m_column2.GetZ() + m_column3.GetX()*m_column1.GetZ()*m_column2.GetY(),
                                  m_column0.GetX()*m_column2.GetY()*m_column3.GetZ() - m_column0.GetX()*m_column2.GetZ()*m_column3.GetY() - m_column2.GetX()*m_column0.GetY()*m_column3.GetZ() + m_column2.GetX()*m_column0.GetZ()*m_column3.GetY() + m_column3.GetX()*m_column0.GetY()*m_column2.GetZ() - m_column3.GetX()*m_column0.GetZ()*m_column2.GetY(),
                                  -m_column0.GetX()*m_column1.GetY()*m_column3.GetZ() + m_column0.GetX()*m_column1.GetZ()*m_column3.GetY() + m_column1.GetX()*m_column0.GetY()*m_column3.GetZ() - m_column1.GetX()*m_column0.GetZ()*m_column3.GetY() - m_column3.GetX()*m_column0.GetY()*m_column1.GetZ() + m_column3.GetX()*m_column0.GetZ()*m_column1.GetY(),
                                  m_column0.GetX()*m_column1.GetY()*m_column2.GetZ() - m_column0.GetX()*m_column1.GetZ()*m_column2.GetY() - m_column1.GetX()*m_column0.GetY()*m_column2.GetZ() + m_column1.GetX()*m_column0.GetZ()*m_column2.GetY() + m_column2.GetX()*m_column0.GetY()*m_column1.GetZ() - m_column2.GetX()*m_column0.GetZ()*m_column1.GetY());

    float determinant = m_column0 * SaVector4(column0.GetX(), column1.GetX(), column2.GetX(), column3.GetX());

    if (determinant == 0)
    {
        SA_FAIL("Can't invert!");
        return false;
    }

    determinant = 1.0f / determinant;

    rOutMatrix.SetColumn0(column0 * determinant);
    rOutMatrix.SetColumn1(column1 * determinant);
    rOutMatrix.SetColumn2(column2 * determinant);
    rOutMatrix.SetColumn3(column3 * determinant);

    return true;
}

SaMatrix44& SaMatrix44::Orthonormalise()
{
    m_column0.Normalise();
    m_column1.Normalise();

    m_column2 = m_column0.Cross(m_column1);
    m_column1 = m_column2.Cross(m_column0);

    return *this;
}

SaMatrix44 SaMatrix44::GetOrthonormalised() const
{
    SaMatrix44 mat = *this;
    mat.Orthonormalise();
    return mat;
}

void SaMatrix44::SetToIdentity()
{
    m_column0.Set(1.0f, 0.0f, 0.0f, 0.0f);
    m_column1.Set(0.0f, 1.0f, 0.0f, 0.0f);
    m_column2.Set(0.0f, 0.0f, 1.0f, 0.0f);
    m_column3.Set(0.0f, 0.0f, 0.0f, 1.0f);
}

void SaMatrix44::SetAllZeros()
{
    m_column0.Set(0.0f, 0.0f, 0.0f, 0.0f);
    m_column1.Set(0.0f, 0.0f, 0.0f, 0.0f);
    m_column2.Set(0.0f, 0.0f, 0.0f, 0.0f);
    m_column3.Set(0.0f, 0.0f, 0.0f, 0.0f);
}

//Static utility functions for creating matrices.
SaMatrix44 SaMatrix44::CreateXRotation(const float rad)
{
    float cos = cosf(rad);
    float sin = sinf(rad);

    SaMatrix44 mat;
    mat.SetToIdentity();
    mat.m_column1.Set(0.0f, cos, sin, 0.0f);
    mat.m_column2.Set(0.0f, -sin, cos, 0.0f);

    return mat;
}

SaMatrix44 SaMatrix44::CreateYRotation(const float rad)
{
    float cos = cosf(rad);
    float sin = sinf(rad);

    SaMatrix44 mat;
    mat.SetToIdentity();
    mat.m_column0.Set(cos, 0.0f, -sin, 0.0f);
    mat.m_column2.Set(sin, 0.0f, cos, 0.0f);

    return mat;
}

SaMatrix44 SaMatrix44::CreateZRotation(const float rad)
{
    float cos = cosf(rad);
    float sin = sinf(rad);

    SaMatrix44 mat;
    mat.SetToIdentity();
    mat.m_column0.Set(cos, sin, 0.0f, 0.0f);
    mat.m_column1.Set(-sin, cos, 0.0f, 0.0f);

    return mat;
}

SaMatrix44 SaMatrix44::CreateRotation(const SaVector3& rAxis, const float rad)
{
    SA_ASSERT(rAxis.Length() > 0.99f && rAxis.Length() < 1.01, "Has to be a unit vector.");

    float x = rAxis.GetX();
    float y = rAxis.GetY();
    float z = rAxis.GetZ();

    float cos = cosf(rad);
    float sin = sinf(rad);
    float ver = 1.0f-cos;

    SaMatrix44 mat;

    mat.m_column0.Set(ver*x*x + cos, ver*x*y + sin*z, ver*x*z - sin*y, 0.0f);
    mat.m_column1.Set(ver*x*y - sin*z, ver*y*y + cos, ver*y*z + sin*x, 0.0f);
    mat.m_column2.Set(ver*x*y + sin*y, ver*y*z - sin*x, ver*z*z + cos, 0.0f);
    mat.m_column3.Set(0.0f, 0.0f, 0.0f, 1.0f);

    return mat;
}

SaMatrix44 SaMatrix44::CreateRotation(const float pitch, const float yaw,  const float roll)
{
    if (pitch == 0.0f && yaw == 0.0f && roll == 0.0f)
    {
        return SaMatrix44::IDENTITY;
    }

    //Calculate the arbitrary axis to rotate around and pass into the above function.
    SaVector3 xAxis = SaVector3::X_AXIS * pitch;
    SaVector3 yAxis = SaVector3::Y_AXIS * yaw;
    SaVector3 zAxis = SaVector3::Z_AXIS * roll;

    SaVector3 arbAxis = xAxis + yAxis + zAxis;
    float rad = arbAxis.Normalise();

    return CreateRotation(arbAxis, rad);
}

SaMatrix44 SaMatrix44::CreateScale(const float x, const float y, const float z)
{
    SaMatrix44 mat;
    mat.m_column0.Set(x, 0.0f, 0.0f, 0.0f);
    mat.m_column1.Set(0.0f, y, 0.0f, 0.0f);
    mat.m_column2.Set(0.0f, 0.0f, z, 0.0f);
    mat.m_column3.Set(0.0f, 0.0f, 0.0f, 1.0f);

    return mat;
}

SaMatrix44 SaMatrix44::CreateScaleUniform(const float scale)
{
    return CreateScale(scale, scale, scale);
}

SaMatrix44 SaMatrix44::CreateTranslation(const float x, const float y, const float z)
{
    SaMatrix44 mat;
    mat.SetToIdentity();
    mat.m_column3.Set(x, y, z, 1.0f);

    return mat;
}

SaMatrix44 SaMatrix44::CreateOrthographicProjection(const float left, const float right,
                                                    const float bottom, const float top,
                                                    const float near, const float far)
{
    SaMatrix44 mat;
    mat.m_column0.Set(2.0f/(right-left), 0.0f, 0.0f, 0.0f);
    mat.m_column1.Set(0.0f, 2.0f/(top-bottom), 0.0f, 0.0f);
    mat.m_column2.Set(0.0f, 0.0f, -2.0f/(far-near), 0.0f);
    mat.m_column3.Set(-(right+left)/(right-left), -(top+bottom)/(top-bottom), -(far+near)/(far-near), 1.0f);
    
    return mat;
}

SaMatrix44 SaMatrix44::CreatePerspectiveProjection(const float fov, const float aspect,
                                                   const float near, const float far)
{
    SA_ASSERT(near > 0.0f, "Near and far must be positive.");
    SA_ASSERT(far > near, "Far must be greater than near.");

    SaMatrix44 mat;
    mat.SetToIdentity();

    float radians = fov / 2.0f * SA_PI / 180.0f;
    float sine = sin(radians);
    float deltaZ = far - near;

    if (deltaZ != 0 && sine != 0 && aspect != 0)
    {
        float fCotangent = cos(radians) / sine;
        mat.m_column0.Set(fCotangent / aspect, 0.0f, 0.0f, 0.0f);
        mat.m_column1.Set(0.0f, fCotangent, 0.0f, 0.0f);
        mat.m_column2.Set(0.0f, 0.0f, -(far + near) / deltaZ, -1.0f);
        mat.m_column3.Set(0.0f, 0.0f, -2.0f * near * far / deltaZ, 0.0f);
    }

    return mat;
}

SaMatrix44 SaMatrix44::CreateLookAt(const SaVector3& vPos, const SaVector3& vLookAt, const SaVector3& vUp)
{
    SaMatrix44 mat;

    SaVector3 zAxis = vPos - vLookAt;
    zAxis.Normalise();
    SaVector3 xAxis = vUp.Cross(zAxis);
    xAxis.Normalise();
    SaVector3 yAxis = zAxis.Cross(xAxis);

    mat.m_column0.Set(xAxis.GetX(), yAxis.GetX(), zAxis.GetX(), 0.0f);
    mat.m_column1.Set(xAxis.GetY(), yAxis.GetY(), zAxis.GetY(), 0.0f);
    mat.m_column2.Set(xAxis.GetZ(), yAxis.GetZ(), zAxis.GetZ(), 0.0f);
    mat.m_column3.Set(-xAxis * vPos, -yAxis * vPos, -zAxis * vPos, 1.0f);

    return mat;
}
