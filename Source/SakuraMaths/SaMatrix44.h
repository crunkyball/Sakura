/*************************************************************
Sakura Game Framework : SaMatrix44.h
Author: Darrell Blake

Column-major matrix class using column vectors. As such vectors 
will need be be post-multipiled: i.e. v = m*v.
*************************************************************/

#ifndef _SA_MATRIX_44_H
#define _SA_MATRIX_44_H

#include <Sakura/SaCore.h>
#include "SaVector4.h"
#include "SaVector3.h"

namespace SakuraMaths
{
    class SaMatrix44
    {      
    public:
        //Useful constants.
        static const SaMatrix44 ALL_ZERO;
        static const SaMatrix44 IDENTITY;

        //Constructors.
        SaMatrix44();
        SaMatrix44(float m00, float m01, float m02, float m03,
                   float m10, float m11, float m12, float m13,
                   float m20, float m21, float m22, float m23,
                   float m30, float m31, float m32, float m33);
        SaMatrix44(const SaVector4& col0,
                   const SaVector4& col1,
                   const SaVector4& col2,
                   const SaVector4& col3);
        SaMatrix44(const SaMatrix44& rMat);
        ~SaMatrix44();
        
        //Operations.
        SaMatrix44& operator =(const SaMatrix44& rMat);
        bool operator ==(const SaMatrix44& rMat) const;
        bool operator !=(const SaMatrix44& rMat) const;
        SaMatrix44 operator +(const SaMatrix44& rMat) const;
        SaMatrix44 operator -(const SaMatrix44& rMat) const;
        SaMatrix44 operator *(const float val) const;
        SaMatrix44 operator *(const SaMatrix44& rMat) const;
        SaMatrix44 operator /(const float val) const;
        
        SaMatrix44& operator +=(const SaMatrix44& rMat);
        SaMatrix44& operator -=(const SaMatrix44& rMat);
        SaMatrix44& operator *=(const float val);
        SaMatrix44& operator *=(const SaMatrix44& rMat);
        SaMatrix44& operator /=(const float val);
        
        //Vector multiplication. This is essentially just 44x41 matrix multiplication 
        //so it returns 41 matrix (or just a four element column vector).
        SaVector4 operator *(const SaVector4& rVec) const;

        SaMatrix44& Transpose();
        SaMatrix44 GetTransposed() const;

        bool GetInverse(SaMatrix44& rOutMatrix);

        SaMatrix44& Orthonormalise();
        SaMatrix44 GetOrthonormalised() const;

        void SetToIdentity();
        void SetAllZeros();

        //Accessors.
        inline const SaVector4& GetColumn0() const { return m_column0; }    //Left
        inline const SaVector4& GetColumn1() const { return m_column1; }    //Up
        inline const SaVector4& GetColumn2() const { return m_column2; }    //Forward
        inline const SaVector4& GetColumn3() const { return m_column3; }    //Translation
        
        inline void SetColumn0(const SaVector4& rVec) { m_column0 = rVec; }
        inline void SetColumn1(const SaVector4& rVec) { m_column1 = rVec; }
        inline void SetColumn2(const SaVector4& rVec) { m_column2 = rVec; }
        inline void SetColumn3(const SaVector4& rVec) { m_column3 = rVec; }

        inline const SaVector4 GetRow0() const { return SaVector4(m_column0.m_x, m_column1.m_x, m_column2.m_x, m_column3.m_x); }
        inline const SaVector4 GetRow1() const { return SaVector4(m_column0.m_y, m_column1.m_y, m_column2.m_y, m_column3.m_y); }
        inline const SaVector4 GetRow2() const { return SaVector4(m_column0.m_z, m_column1.m_z, m_column2.m_z, m_column3.m_z); }
        inline const SaVector4 GetRow3() const { return SaVector4(m_column0.m_w, m_column1.m_w, m_column2.m_w, m_column3.m_w); }

        //Static utility functions for creating matrices.
        static SaMatrix44 CreateXRotation(const float rad);
        static SaMatrix44 CreateYRotation(const float rad);
        static SaMatrix44 CreateZRotation(const float rad);

        //Rotation about an arbitrary axis. Use this or quaternions to avoid gimbal lock.
        static SaMatrix44 CreateRotation(const SaVector3& rAxis, const float rad);
        static SaMatrix44 CreateRotation(const float pitch, const float yaw, const float roll);

        static SaMatrix44 CreateScale(const float x, const float y, const float z);
        static SaMatrix44 CreateScaleUniform(const float scale);

        static SaMatrix44 CreateTranslation(const float x, const float y, const float z);
        
        static SaMatrix44 CreateOrthographicProjection(const float left, const float right,
                                                       const float bottom, const float top,
                                                       const float near, const float far);
        static SaMatrix44 CreatePerspectiveProjection(const float fov, const float aspect,
                                                      const float near, const float far);

        static SaMatrix44 CreateLookAt(const SaVector3& vPos, const SaVector3& vLookAt, const SaVector3& vUp);

    private:
        SaVector4 m_column0;
        SaVector4 m_column1;
        SaVector4 m_column2;
        SaVector4 m_column3;
    };
}

#endif  //_SA_MATRIX_44_H
