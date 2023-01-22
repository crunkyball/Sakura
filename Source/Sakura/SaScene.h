/*************************************************************
Sakura Game Framework : SaScene.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_SCENE_H
#define _SA_SCENE_H

#include "SaCore.h"

namespace Sakura
{
    class SaCamera;

    class SaScene
    {
    public:
        SaScene();
        ~SaScene();

        void Update(uint32_t dt);
        void Render();

    private:
        bool m_bDrawGrid;
        bool m_bDrawAxes;
    };
}

#endif
