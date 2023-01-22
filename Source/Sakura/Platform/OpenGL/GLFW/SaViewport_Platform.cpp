/*************************************************************
Sakura Game Framework : SaViewport_Platform.cpp
Author: Darrell Blake

OpenGL/GLFW platform implementation for SaViewport.
*************************************************************/

#include "SaViewport_Platform.h"
#include "../../../SaViewport.h"
#include "../SaGraphicsAPI.h"

using namespace Sakura;

SaViewport_Platform::SaViewport_Platform(SaViewport* pParent) : 
    m_pParent(pParent)
{
}

void SaViewport_Platform::PreRender()
{
    glViewport(m_pParent->m_xPosition, m_pParent->m_yPosition, m_pParent->m_width, m_pParent->m_height);
    glScissor(m_pParent->m_xPosition, m_pParent->m_yPosition, m_pParent->m_width, m_pParent->m_height);
    glClearColor(m_pParent->m_clearColour.GetR(), 
                 m_pParent->m_clearColour.GetG(), 
                 m_pParent->m_clearColour.GetB(), 
                 m_pParent->m_clearColour.GetA());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
