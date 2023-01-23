/*************************************************************
Sakura Game Framework : SaModel_Platform.cpp
Author: Darrell Blake

OpenGL implementation for SaModel.
*************************************************************/

#include "SaModel_Platform.h"
#include <SakuraMaths/SaVector3.h>
#include "../../SaModel.h"
#include "../../SaEffect.h"
#include "../../SaColour.h"

using namespace Sakura;
using namespace SakuraMaths;

SaModel_Platform::SaModel_Platform(SaModel* pParent) : 
    m_pParent(pParent)
{
}

bool SaModel_Platform::Load()
{
    CheckOpenGLError("Already errored somewhere!");
    
    glGenBuffers(1, &m_vertBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_pParent->m_numVertices * sizeof(SaModel::Vertex), m_pParent->m_pVertices, GL_STATIC_DRAW);

    glGenBuffers(1, &m_indicesBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indicesBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_pParent->m_numTriangles * sizeof(SaModel::Triangle), m_pParent->m_pTriangles, GL_STATIC_DRAW);

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    if (CheckOpenGLError("Loading model"))
        return false;

    return true;
}

bool SaModel_Platform::Unload()
{
    CheckOpenGLError("Already errored somewhere!");

    glDeleteBuffers(1, &m_vertBuffer);
    glDeleteBuffers(1, &m_indicesBuffer);
    glDeleteVertexArrays(1, &m_vao);

    if (CheckOpenGLError("Unloading model"))
        return false;

    return true;
    
    return false;
}

void SaModel_Platform::Render()
{   
    CheckOpenGLError("Already errored somewhere");

    glBindVertexArray(m_vao);

    //If the model is static we could just do this in the load function and then the 
    //call to glBindVertexArray above will be sufficient. I'll come back and add this 
    //optimisation later (promise).
    glBindBuffer(GL_ARRAY_BUFFER, m_vertBuffer);
    glVertexAttribPointer(SaEffect::POSITION_ATTR, 3, GL_FLOAT, GL_FALSE, sizeof(SaModel::Vertex), 0);
    glVertexAttribPointer(SaEffect::NORMAL_ATTR, 3, GL_FLOAT, GL_FALSE, sizeof(SaModel::Vertex), reinterpret_cast<void*>(sizeof(SaVector3)));
    glEnableVertexAttribArray(SaEffect::POSITION_ATTR);
    glEnableVertexAttribArray(SaEffect::NORMAL_ATTR);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indicesBuffer);
    
    glDrawElements(GL_TRIANGLES, m_pParent->m_numTriangles * 3, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(SaEffect::NORMAL_ATTR);
    glDisableVertexAttribArray(SaEffect::POSITION_ATTR);

    CheckOpenGLError("Rendering model");
}
