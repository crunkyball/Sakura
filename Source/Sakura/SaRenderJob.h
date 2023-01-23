/*************************************************************
Sakura Game Framework : SaRenderJob.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_RENDER_JOB_H
#define _SA_RENDER_JOB_H

#include "SaCallback.h"
#include "SaShader.h"
#include "SaColour.h"
#include <SakuraMaths/SaMatrix44.h>
#include <SakuraMaths/SaVector2.h>
#include <SakuraMaths/SaVector3.h>

namespace Sakura
{
    class SaTexture;

    class SaRenderJob
    {
    public:
        SaRenderJob();
        SaRenderJob(SaCallback<const SaRenderJob*> jobFunc);

        void                            SetEnable(bool enable) { m_enable = enable; }
        bool                            GetEnable() const { return m_enable; }

        void                            SetData(const uint8_t* pData, uint32_t dataIdx = 0) { m_pData[dataIdx] = pData; }
        const uint8_t*                  GetData(uint32_t dataIdx = 0) const { return m_pData[dataIdx]; }

        void                            SetDataSize(uint32_t dataSize, uint32_t dataIdx = 0) { m_dataSize[dataIdx] = dataSize; }
        const uint32_t                  GetDataSize(uint32_t dataIdx = 0) const { return m_dataSize[dataIdx]; }

        void                            SetShaderType(const SaShaderType shaderType) { m_shaderType = shaderType; }
        const SaShaderType              GetShaderType() const { return m_shaderType; }

        void                            SetName(const char* pName) { m_pName = pName; }
        const char*                     GetName() const { return m_pName; }

        void                            SetInt(const int var) { m_int = var; }
        const int                       GetInt() const { return m_int; }

        void                            SetFloat(const float var) { m_float = var; }
        const float                     GetFloat() const { return m_float; }

        void                            SetVector2(const SakuraMaths::SaVector2& rVec, uint32_t posIdx = 0) { m_vector2D[posIdx] = rVec; }
        const SakuraMaths::SaVector2&   GetVector2(uint32_t posIdx = 0) const { return m_vector2D[posIdx]; }

        void                            SetVector3(const SakuraMaths::SaVector3& rVec, uint32_t posIdx = 0) { m_vector3D[posIdx] = rVec; }
        const SakuraMaths::SaVector3&   GetVector3(uint32_t posIdx = 0) const { return m_vector3D[posIdx]; }

        void                            SetMatrix(const SakuraMaths::SaMatrix44& rMatrix) { m_matrix = rMatrix; }
        const SakuraMaths::SaMatrix44&  GetMatrix() const { return m_matrix; }

        void                            SetColour(const SaColour& rColour) { m_colour = rColour; }
        const SaColour&                 GetColour() const { return m_colour; }

        void                            SetTexture(const SaTexture* pTexture) { m_pTexture = pTexture; }
        const SaTexture*                GetTexture() const { return m_pTexture; }

        void                            Process();

    private:
        SaCallback<const SaRenderJob*>  m_jobFunc;

        static const uint32_t   NUM_DATA_ITEMS = 2;
        static const uint32_t   NUM_VECTOR_ITEMS = 4;

        //TODO: I'm a bit worried about the number of members re cache misses.
        //Perhaps there's a better solution. Come back to this.
        bool                    m_enable;
        const uint8_t*          m_pData[NUM_DATA_ITEMS];
        uint32_t                m_dataSize[NUM_DATA_ITEMS];
        SaShaderType            m_shaderType;
        const char*             m_pName;
        int                     m_int;
        float                   m_float;
        SakuraMaths::SaVector2  m_vector2D[NUM_VECTOR_ITEMS];
        SakuraMaths::SaVector3  m_vector3D[NUM_VECTOR_ITEMS];
        SakuraMaths::SaMatrix44 m_matrix;
        SaColour                m_colour;
        const SaTexture*        m_pTexture;
    };
}

#endif  //_SA_RENDER_JOB_H
