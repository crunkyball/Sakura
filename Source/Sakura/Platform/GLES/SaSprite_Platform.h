/***************************************************
Sakura Game Framework : SaSprite_Platform.h
Author: Darrell Blake

OpenGL ES platform implementation for SaSprite.
***************************************************/

#ifndef _SA_SPRITE_PLATFORM_H
#define _SA_SPRITE_PLATFORM_H

#include "../../SaCore.h"

namespace Sakura
{
    class SaSprite_Platform
    {
    public:
        SaSprite_Platform();

        void Create();
        void Release();

        void Render();

    private:
        uint32_t m_vbo[2];
    };
};

#endif  //_SA_SPRITE_PLATFORM_H
