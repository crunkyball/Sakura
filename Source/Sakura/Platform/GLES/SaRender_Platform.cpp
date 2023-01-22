/*************************************************************
Sakura Game Framework : SaRender_Platform.cpp
Author: Darrell Blake

OpenGL ES platform implementation for SaRender.
*************************************************************/

#include "../../SaRender.h"
#include "SaGraphicsAPI.h"

using namespace Sakura;

void SaRender::RenderThread_SetDepthTest(bool enable)
{
    if (enable)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);
}

void SaRender::RenderThread_SetAlphaBlending(bool enable)
{
    //Probably need to offer more options but this will do for now.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (enable)
        glEnable(GL_BLEND);
    else
        glDisable(GL_BLEND);
}

void SaRender::RenderThread_SetBackFaceCulling(bool enable)
{
    glCullFace(GL_BACK);

    if (enable)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);
}
