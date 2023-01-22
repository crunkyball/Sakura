/*************************************************************
Sakura Game Framework : SaModel_Platform.h
Author: Darrell Blake

OpenGL ES platform implementation for SaModel.
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
    };
};

#endif  //_SA_MODEL_PLATFORM_H
