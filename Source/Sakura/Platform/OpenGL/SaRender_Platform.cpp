/*************************************************************
Sakura Game Framework : SaRender_Platform.cpp
Author: Darrell Blake

OpenGL platform implementation for SaRender.
*************************************************************/

#include "../../SaRender.h"
#include "SaGraphicsAPI.h"

using namespace Sakura;

void SaRender::RenderThread_SetDepthTest(bool enable)
{
    CheckOpenGLError("Already errored somewhere");

    if (enable)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);

    CheckOpenGLError("Setting depth test");
}

void SaRender::RenderThread_SetAlphaBlending(bool enable)
{
    CheckOpenGLError("Already errored somewhere");

    //Probably need to offer more options but this will do for now.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (enable)
        glEnable(GL_BLEND);
    else
        glDisable(GL_BLEND);

    CheckOpenGLError("Setting alpha blending");
}

void SaRender::RenderThread_SetBackFaceCulling(bool enable)
{
    CheckOpenGLError("Already errored somewhere");

    glCullFace(GL_BACK);

    if (enable)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);

    CheckOpenGLError("Setting back face culling");
}
