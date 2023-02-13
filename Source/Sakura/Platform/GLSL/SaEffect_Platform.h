/***************************************************
Sakura Game Framework : SaEffect_Platform.h
Author: Darrell Blake

GLSL platform implementation for SaEffect.
***************************************************/

#ifndef _SA_EFFECT_PLATFORM_H
#define _SA_EFFECT_PLATFORM_H

#include "../../SaCore.h"
#include "../../SaHashTable.h"
#include "../../SaShader.h"

namespace SakuraMaths
{
    class SaVector3;
    class SaMatrix44;
}

namespace Sakura
{
    class SaEffect;
    class SaColour;
    class SaTexture;

    class SaEffect_Platform
    {
    public:
        SaEffect_Platform(SaEffect* pParent);

        static void Initialise();

        bool Load(const uint8_t* pVertexShaderData, const uint8_t* pFragmentShaderData);
        bool Unload();

        void SetIntParameter(SaShaderType shaderType, const char* pParameterName, const int val);
        void SetFloatParameter(SaShaderType shaderType, const char* pParameterName, const float val);
        void SetVectorParameter(SaShaderType shaderType, const char* pParameterName, const SakuraMaths::SaVector3& rVector);
        void SetMatrixParameter(SaShaderType shaderType, const char* pParameterName, const SakuraMaths::SaMatrix44& rMatrix);
        void SetColourParameter(SaShaderType shaderType, const char* pParameterName, const SaColour& rColour);
        void SetTextureParameter(SaShaderType shaderType, const char* pParameterName, const SaTexture* pTexture);

        void Enable();
        void Disable();

        static const char* FILE_EXTENSION;
    private:
        void PrintError(int32_t handle, const char* reason);

        int32_t m_vertexShaderHandle;
        int32_t m_fragmentShaderHandle;
        int32_t m_programHandle;

        SaHashTable<const char*, int32_t> m_uniforms;
    };
}

#endif  //_SA_EFFECT_PLATFORM_H
