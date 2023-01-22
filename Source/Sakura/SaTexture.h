/*************************************************************
Sakura Game Framework : SaTexture.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_TEXTURE_H
#define _SA_TEXTURE_H

#include "SaCore.h"
#include "SaCallback.h"
#include PLATFORM_INCLUDE( SA_RENDER_API_DIR/SaTexture_Platform.h )

namespace Sakura
{
    class SaFile;
    class SaRenderJob;
    
    class SaTexture
    {
        friend class SaTexture_Platform;

    public:
        enum EState
        {
            STATE_UNLOADED,
            STATE_LOADED,
            STATE_ERROR
        };

        SaTexture();
        
        void Load(const uint8_t* pFileData, const uint32_t fileDataSize, SaCallback<bool> callback = NO_CALLBACK);
        void Unload(SaCallback<bool> callback = NO_CALLBACK);

        void GetDimensions(uint32_t& rWidth, uint32_t& rHeight) const ;

        const SaTexture_Platform& GetPlatformTexture() const;
       
#ifdef SA_BUILD_DEBUG
        void SetDebugName(const char* pDebugName) { m_pDebugName = pDebugName; }
        const char* GetDebugName() const { return m_pDebugName; }
#endif

    private:
        void RenderThread_Load(const SaRenderJob* pJob);
        void RenderThread_Unload(const SaRenderJob* pJob);

        SaTexture_Platform m_platformTexture;

        EState      m_state;
        uint32_t    m_width;
        uint32_t    m_height;
        uint32_t    m_bitDepth;

        SaCallback<bool> m_loadFinishedCallback;

#ifdef SA_BUILD_DEBUG
        const char* m_pDebugName;
#endif
    };
}

#endif
