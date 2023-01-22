/*************************************************************
Sakura Game Framework : SaEffect.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_EFFECT_H
#define _SA_EFFECT_H

#include "SaCore.h"
#include "SaFileHandle.h"
#include "SaShader.h"
#include PLATFORM_INCLUDE( SA_RENDER_API_DIR/SaGraphicsAPI.h )
#include PLATFORM_INCLUDE( SA_EFFECT_API_DIR/SaEffect_Platform.h )

namespace SakuraMaths
{
    class SaVector3;
    class SaMatrix44;
}

namespace Sakura
{
    class SaColour;
    class SaTexture;
    class SaFile;
    class SaRenderJob;

    class SaEffect
    {
        friend class SaEffect_Platform;

    public:
        enum EVertexAttribute
        {
            POSITION_ATTR   = 0,
            COLOUR_ATTR     = 1,
            TEXCOORD0_ATTR  = 2,
            NORMAL_ATTR     = 3
        };

        enum EState
        {
            STATE_UNLOADED,
            STATE_LOADED,
            STATE_ERROR
        };

        SaEffect();

        static void Initialise();

        void Load(const uint8_t* pVertexShaderData, const uint8_t* pFragmentShaderData, SaCallback<bool> callback = NO_CALLBACK);
        void Unload(SaCallback<bool> callback = NO_CALLBACK);

        void SetIntParameter(SaShaderType shaderType, const char* pParameterName, const int32_t val);
        void SetFloatParameter(SaShaderType shaderType, const char* pParameterName, const float val);
        void SetVectorParameter(SaShaderType shaderType, const char* pParameterName, const SakuraMaths::SaVector3& rVector);
        void SetMatrixParameter(SaShaderType shaderType, const char* pParameterName, const SakuraMaths::SaMatrix44& rMatrix);
        void SetColourParameter(SaShaderType shaderType, const char* pParameterName, const SaColour& rColour);
        void SetTextureParameter(SaShaderType shaderType, const char* pParameterName, const SaTexture* pTexture);

        void Enable();
        void Disable();

#ifdef SA_BUILD_DEBUG
        void SetDebugName(const char* pDebugName) { m_pDebugName = pDebugName; }
        const char* GetDebugName() const { return m_pDebugName; }
#endif

    private:
        static void RenderThread_Initialise(const SaRenderJob* pJob);

        void RenderThread_Load(const SaRenderJob* pJob);
        void RenderThread_Unload(const SaRenderJob* pJob);
        void RenderThread_Enable(const SaRenderJob* pJob);
        void RenderThread_Disable(const SaRenderJob* pJob);
        void RenderThread_SetIntParameter(const SaRenderJob* pJob);
        void RenderThread_SetFloatParameter(const SaRenderJob* pJob);
        void RenderThread_SetVectorParameter(const SaRenderJob* pJob);
        void RenderThread_SetMatrixParameter(const SaRenderJob* pJob);
        void RenderThread_SetColourParameter(const SaRenderJob* pJob);
        void RenderThread_SetTextureParameter(const SaRenderJob* pJob);

        SaEffect_Platform m_platformEffect;

        EState      m_state;

        static bool ms_locked;
        bool        m_enabled;

        SaCallback<bool> m_loadFinishedCallback;

#ifdef SA_BUILD_DEBUG
        const char* m_pDebugName;
#endif
    };
}

#endif  //_SA_EFFECT_H
