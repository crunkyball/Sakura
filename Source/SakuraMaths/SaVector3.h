/*************************************************************
Sakura Game Framework : SaVector3.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_VECTOR_3_H
#define _SA_VECTOR_3_H

#include <Sakura/SaCore.h>

namespace SakuraMaths
{
    class SaVector3
    {
        friend class SaVector4;
        friend class SaMatrix33;
        
    public:
        //Useful constants.
        static const SaVector3 ALL_ZERO;
        static const SaVector3 X_AXIS;
        static const SaVector3 Y_AXIS;
        static const SaVector3 Z_AXIS;

        SaVector3();
        SaVector3(const float x, const float y, const float z);
        SaVector3(const SaVector3& rVec);
        ~SaVector3();
        
        //Operators.
        SaVector3& operator =(const SaVector3& rVec);
        bool operator ==(const SaVector3& rVec) const;
        bool operator !=(const SaVector3& rVec) const;
        SaVector3 operator +(const SaVector3& rVec) const;
        SaVector3 operator -(const SaVector3& rVec) const;
        SaVector3 operator *(const float val) const;
        float operator *(const SaVector3& rVec) const;  //Dot product.
        SaVector3 operator /(const float val) const;
        SaVector3 operator -() const;
        SaVector3& operator +=(const SaVector3& rVec);
        SaVector3& operator -=(const SaVector3& rVec);
        SaVector3& operator *=(const float val);
        SaVector3& operator /=(const float val);

        float Length() const;
        float LengthSquared() const;
        float Normalise();
        SaVector3 GetNormalised(float* pLength = NULL) const;
        SaVector3 Cross(const SaVector3& rVec) const;
        
        //Accessors.
        void Set(const float x, const float y, const float z);
        inline float GetX() const { return m_x; }
        inline float GetY() const { return m_y; }
        inline float GetZ() const { return m_z; }
        
    private:
        float m_x;
        float m_y;
        float m_z;
    };
}

#endif  //_SA_VECTOR_3_H
