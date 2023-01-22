/*************************************************************
Sakura Game Framework : SaVector4.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_VECTOR_4_H
#define _SA_VECTOR_4_H

#include <Sakura/SaCore.h>
#include "SaVector3.h"

namespace SakuraMaths
{
    class SaVector4
    {
        friend class SaMatrix44;
        
    public:
        //Useful constants.
        static const SaVector4 ALL_ZERO;
        static const SaVector4 X_AXIS;
        static const SaVector4 Y_AXIS;
        static const SaVector4 Z_AXIS;
        static const SaVector4 W_AXIS;

        SaVector4();
        SaVector4(const float x, const float y, const float z, const float w);
        SaVector4(const SaVector3&, const float w);
        SaVector4(const SaVector4& rVec);
        ~SaVector4();
        
        SaVector4& operator =(const SaVector4& rVec);
        bool operator ==(const SaVector4& rVec) const;
        bool operator !=(const SaVector4& rVec) const;
        SaVector4 operator +(const SaVector4& rVec) const;
        SaVector4 operator -(const SaVector4& rVec) const;
        SaVector4 operator *(const float val) const;
        float operator *(const SaVector4& rVec) const;  //Dot product.
        SaVector4 operator /(const float val) const;
        SaVector4 operator -() const;
        SaVector4& operator +=(const SaVector4& rVec);
        SaVector4& operator -=(const SaVector4& rVec);
        SaVector4& operator *=(const float val);
        SaVector4& operator /=(const float val);
        
        float Length() const;
        float LengthSquared() const;
        float Normalise();
        SaVector4 GetNormalised(float* pLength = NULL) const;
        SaVector4 Cross(const SaVector4& rVec) const;
        
        //Accessors.
        void Set(const float x, const float y, const float z, const float w);
        inline float GetX() const { return m_x; }
        inline float GetY() const { return m_y; }
        inline float GetZ() const { return m_z; }
        inline float GetW() const { return m_w; }
        inline SaVector3 GetXYZ() const { return SaVector3(m_x, m_y, m_z); }
        
    private:
        float m_x;
        float m_y;
        float m_z;
        float m_w;
    };
}

#endif  //_SA_VECTOR_4_H
