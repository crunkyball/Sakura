/*************************************************************
Sakura Game Framework : SaEffect_Platform.h
Author: Darrell Blake

Cg platform implementation for SaEffect.
*************************************************************/

#include "../../SaCore.h"
#include "../../SaHashTable.h"
#include "../../SaShader.h"
#include <Cg/cg.h>
#include <Cg/cgGL.h>

#ifndef _SA_EFFECT_PLATFORM_H
#define _SA_EFFECT_PLATFORM_H

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

        static bool Initialise();

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

        static bool CheckCgError();

        static const char* FILE_EXTENSION;
    private:
        static CGcontext ms_cgContext;
        static CGprofile ms_vertexProfile;
        static CGprofile ms_fragmentProfile;

        SaEffect*   m_pParent;

        void PopulateParams(CGparameter param, SaHashTable<const char*, CGparameter>& paramTable);
        CGparameter* GetParameter(SaShaderType shaderType, const char* pParameterName);

        CGprogram m_vertexProgram;
        SaHashTable<const char*, CGparameter> m_vertexParameters;

        CGprogram m_fragmentProgram;
        SaHashTable<const char*, CGparameter> m_fragmentParameters;
    };
}

#endif  //_SA_EFFECT_PLATFORM_H
