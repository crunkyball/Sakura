/*************************************************************
Sakura Game Framework : SaTexture_Platform.h
Author: Darrell Blake

OpenGL platform implementation for SaTexture.
*************************************************************/

#ifndef _SA_TEXTURE_PLATFORM_H
#define _SA_TEXTURE_PLATFORM_H

#include "../../SaCore.h"

namespace Sakura
{
    class SaTexture;

    class SaTexture_Platform
    {
    public:
        SaTexture_Platform(SaTexture* pParent);

        const uint32_t GetHandle() const;

        bool Load(const uint8_t* pData);
        bool Unload();

    private:
        SaTexture*  m_pParent;
        uint32_t    m_handle;
    };
}

#endif  //_SA_TEXTURE_PLATFORM_H
