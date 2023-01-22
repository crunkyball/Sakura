/*************************************************************
Sakura Game Framework : SaModel.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_MODEL_H
#define _SA_MODEL_H

#include "SaCore.h"
#include "SaColour.h"
#include <SakuraMaths/SaVector3.h>
#include "SaCallback.h"
#include PLATFORM_INCLUDE( SA_RENDER_API_DIR/SaModel_Platform.h )

namespace Sakura
{
    class SaFile;
    class SaRenderJob;

    class SaModel
    {
        friend class SaModel_Platform;

    public:
        enum EState
        {
            STATE_UNLOADED,
            STATE_LOADED,
            STATE_ERROR
        };

        SaModel();

        void Load(const uint8_t* pFileData, const uint32_t fileDataSize, SaCallback<bool> callback = NO_CALLBACK);
        void Unload(SaCallback<bool> callback = NO_CALLBACK);

        void Render();

        const SaColour& GetMaterialColour();

#ifdef SA_BUILD_DEBUG
        void DebugDrawNormals();

        void SetDebugName(const char* pDebugName) { m_pDebugName = pDebugName; }
        const char* GetDebugName() const { return m_pDebugName; }
#endif

    private:
        void RenderThread_Load(const SaRenderJob* pJob);
        void RenderThread_Unload(const SaRenderJob* pJob);
        void RenderThread_Render(const SaRenderJob* pJob);

        struct Vertex
        {
            SakuraMaths::SaVector3 position;
            SakuraMaths::SaVector3 normal;
        };

        struct Triangle
        {
            uint32_t vertIndices[3];
        };

        struct Material
        {
            SaColour diffuseColour;
        };

        static const uint32_t FILE_VERSION = 4;

        SaModel_Platform m_platformModel;

        EState      m_state;
        uint32_t    m_numVertices;
        uint32_t    m_numTriangles;
        Vertex*     m_pVertices;
        Triangle*   m_pTriangles;

        //We currently only support one material per model.
        Material m_material;

        SaCallback<bool> m_loadFinishedCallback;

#ifdef SA_BUILD_DEBUG
        const char* m_pDebugName;
#endif
    };
}

#endif  //_SA_MODEL_H
