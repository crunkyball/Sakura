/*************************************************************
Sakura Game Framework : SaSprite.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_SPRITE_H
#define _SA_SPRITE_H

#include "SaCore.h"
#include <SakuraMaths/SaVector2.h>
#include "SaTexture.h"
#include "SaEffect.h"
#include "SaColour.h"
#include PLATFORM_INCLUDE( SA_RENDER_API_DIR/SaSprite_Platform.h )

namespace SakuraMaths
{
    class SaMatrix44;
}

namespace Sakura
{
    class SaTexture;
    class SaRenderJob;

    class SaSprite
    {
        friend class SaSprite_Platform;

    public:
        SaSprite();
        ~SaSprite();

        void Create(const SaTexture* pTexture, SaEffect* pEffect);

        void SetColour(const SaColour& rColour);
        void SetPosition(const SakuraMaths::SaVector2& rPosition);
        void SetScale(const SakuraMaths::SaVector2& rScale);

        void Render();

    private:
        void RenderThread_Create(const SaRenderJob* pJob);
        void RenderThread_Render(const SaRenderJob* pJob);

        static const SakuraMaths::SaVector2 ms_verts[4];
        static const SakuraMaths::SaVector2 ms_texCoords[4];
        static const uint16_t ms_indices[4];

        SaSprite_Platform m_platformSprite;

        SaEffect* m_pSpriteEffect;

        const SaTexture* m_pTexture;
        SaColour m_colour;
        SakuraMaths::SaVector2 m_position;
        SakuraMaths::SaVector2 m_scale;
    };
}

#endif  //_SA_SPRITE_H
