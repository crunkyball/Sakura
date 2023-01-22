/*************************************************************
Sakura Game Framework : SaMatrix33.h
Author: Darrell Blake

Column-major matrix class using column vectors. As such vectors 
will need be be post-multipiled: i.e. v = m*v.
*************************************************************/

#ifndef _SA_MATRIX_33_H
#define _SA_MATRIX_33_H

#include <Sakura/SaCore.h>
#include "SaVector3.h"

namespace SakuraMaths
{
    class SaMatrix33
    {      
    public:
        //Useful constants.
        static const SaMatrix33 ALL_ZERO;
        static const SaMatrix33 IDENTITY;

        //Constructors.
        SaMatrix33();
        SaMatrix33(float m00, float m01, float m02,
                   float m10, float m11, float m12,
                   float m20, float m21, float m22);
        SaMatrix33(const SaVector3& col0,
                   const SaVector3& col1,
                   const SaVector3& col2);
        SaMatrix33(const SaMatrix33& rMat);
        ~SaMatrix33();
        
        //Operations.
        SaMatrix33& operator =(const SaMatrix33& rMat);
        bool operator ==(const SaMatrix33& rMat) const;
        bool operator !=(const SaMatrix33& rMat) const;
        SaMatrix33 operator +(const SaMatrix33& rMat) const;
        SaMatrix33 operator -(const SaMatrix33& rMat) const;
        SaMatrix33 operator *(const float val) const;
        SaMatrix33 operator *(const SaMatrix33& rMat) const;
        SaMatrix33 operator /(const float val) const;
        
        SaMatrix33& operator +=(const SaMatrix33& rMat);
        SaMatrix33& operator -=(const SaMatrix33& rMat);
        SaMatrix33& operator *=(const float val);
        SaMatrix33& operator *=(const SaMatrix33& rMat);
        SaMatrix33& operator /=(const float val);
        
        //Vector multiplication. This is essentially just 33x31 matrix multiplication 
        //so it returns 31 matrix (or just a three element column vector).
        SaVector3 operator *(const SaVector3& rVec) const;

        SaMatrix33& Transpose();
        SaMatrix33 GetTransposed() const;

        SaMatrix33& Orthonormalise();
        SaMatrix33 GetOrthonormalised() const;

        void SetToIdentity();
        void SetAllZeros();
       
        //Accessors.
        inline const SaVector3& GetColumn0() const { return m_column0; }    //Left
        inline const SaVector3& GetColumn1() const { return m_column1; }    //Up
        inline const SaVector3& GetColumn2() const { return m_column2; }    //Forward

        inline void SetColumn0(const SaVector3& rVec) { m_column0 = rVec; }
        inline void SetColumn1(const SaVector3& rVec) { m_column1 = rVec; }
        inline void SetColumn2(const SaVector3& rVec) { m_column2 = rVec; }
        
        inline const SaVector3 GetRow0() const { return SaVector3(m_column0.m_x, m_column1.m_x, m_column2.m_x); }
        inline const SaVector3 GetRow1() const { return SaVector3(m_column0.m_y, m_column1.m_y, m_column2.m_y); }
        inline const SaVector3 GetRow2() const { return SaVector3(m_column0.m_z, m_column1.m_z, m_column2.m_z); }

        //Static utility functions for creating matrices.
        static SaMatrix33 CreateXRotation(const float rad);
        static SaMatrix33 CreateYRotation(const float rad);
        static SaMatrix33 CreateZRotation(const float rad);

        //Rotation about an arbitrary axis. Use this or quaternions to avoid gimbal lock.
        static SaMatrix33 CreateRotation(const SaVector3& rAxis, const float rad);
        static SaMatrix33 CreateRotation(const float pitch, const float yaw, const float roll);

        static SaMatrix33 CreateScale(const float x, const float y, const float z);
        static SaMatrix33 CreateScaleUniform(const float scale);
        
    private:
        SaVector3 m_column0;
        SaVector3 m_column1;
        SaVector3 m_column2;
    };
}

#endif  //_SA_MATRIX_33_H
