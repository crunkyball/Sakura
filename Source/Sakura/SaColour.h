/*************************************************************
Sakura Game Framework : SaColour.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_COLOUR_H
#define _SA_COLOUR_H

#include "SaCore.h"

namespace Sakura
{
    class SaColour
    {
    public:
        //Useful constants.
        static const SaColour BLACK;
        static const SaColour WHITE;
        static const SaColour RED;
        static const SaColour GREEN;
        static const SaColour BLUE;
        static const SaColour YELLOW;
        static const SaColour MAGENTA;
        static const SaColour CYAN;
        static const SaColour SAKURA;

        SaColour();
        SaColour(float fR, float fG, float fB, float fA);

        SaColour& operator =(const SaColour& rColour);
        bool operator ==(const SaColour& rColour) const;
        bool operator !=(const SaColour& rColour) const;

        //Accessors.
        void Set(const float fR, const float fG, const float fB, const float fA);
        float GetR() const { return m_fR; }
        float GetG() const { return m_fG; }
        float GetB() const { return m_fB; }
        float GetA() const { return m_fA; }

    private:
        float m_fR;
        float m_fG;
        float m_fB;
        float m_fA;
    };
}

#endif  //_SA_COLOUR_H
