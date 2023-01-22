/*************************************************************
Sakura Game Framework : SaModel_Platform.h
Author: Darrell Blake

OpenGL implementation for SaModel.
*************************************************************/

#ifndef _SA_MODEL_PLATFORM_H
#define _SA_MODEL_PLATFORM_H

#include "../../SaCore.h"

namespace Sakura
{
    class SaModel;

    class SaModel_Platform
    {
    public:
        SaModel_Platform(SaModel* pParent);

        bool Load();
        bool Unload();
        void Render();

    private:
        SaModel*    m_pParent;

        uint32_t    m_vao;
        uint32_t    m_vertBuffer;
        uint32_t    m_indicesBuffer;
    };
};

#endif  //_SA_MODEL_PLATFORM_H
