/*************************************************************
Sakura Game Framework : SaLight.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_LIGHT_H
#define _SA_LIGHT_H

#include "SaCore.h"
#include "SaGameObject.h"
#include "SaColour.h"

namespace Sakura
{
    class SaLight : public SaGameObject
    {
    public:
        SaLight();
        virtual ~SaLight();

        void Initialise(const SaColour& rColour);

        void Update(uint32_t dt);

#ifdef SA_BUILD_DEBUG
        void DebugRender();
#endif

        const SaColour& GetColour() const;
        void SetColour(const SaColour& rColour);

    private:
        SaColour m_colour;
    };
}

#endif  //_SA_LIGHT_H
