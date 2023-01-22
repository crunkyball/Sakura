/*************************************************************
Sakura Game Framework : SaVector2.h
Author: Darrell Blake
*************************************************************/


#ifndef _SA_VECTOR_2_H
#define _SA_VECTOR_2_H

#include <Sakura/SaCore.h>

namespace SakuraMaths
{
    class SaVector2
    {
    public:
        //Useful constants.
        static const SaVector2 ALL_ZERO;
        static const SaVector2 ALL_ONE;
        static const SaVector2 X_AXIS;
        static const SaVector2 Y_AXIS;

        SaVector2();
        SaVector2(const float x, const float y);
        SaVector2(const SaVector2& rVec);
        ~SaVector2();

        SaVector2& operator =(const SaVector2& rVec);
        bool operator ==(const SaVector2& rVec) const;
        bool operator !=(const SaVector2& rVec) const;
        SaVector2 operator +(const SaVector2& rVec) const;
        SaVector2 operator -(const SaVector2& rVec) const;
        SaVector2 operator *(const float val) const;
        float operator *(const SaVector2& rVec) const;  //Dot product.
        SaVector2 operator /(const float val) const;
        SaVector2& operator +=(const SaVector2& rVec);
        SaVector2& operator -=(const SaVector2& rVec);
        SaVector2& operator *=(const float val);
        SaVector2& operator /=(const float val);

        float Length() const;
        float LengthSquared() const;
        float Normalise();
        SaVector2 GetNormalised(float* pLength = NULL) const;

        //Accessors.
        void Set(const float x, const float y);
        float GetX() const { return m_x; }
        float GetY() const { return m_y; }

    private:
        float m_x;
        float m_y;
    };
}

#endif  //_SA_VECTOR_2_H
