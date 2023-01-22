/*************************************************************
Sakura Game Framework : SaDebugDraw_Platform.cpp
Author: Darrell Blake

OpenGL platform implementation for SaDebugDraw.
*************************************************************/

#include "../../SaDebugDraw.h"

using namespace Sakura;
using namespace SakuraMaths;

void SaDebugDraw::CreatePrimBuffer(DebugPrims* pPrims)
{
    CheckOpenGLError("Already errored somewhere");

    glGenVertexArrays(1, &pPrims->vao);
    glGenBuffers(2, pPrims->vbo);

    glBindVertexArray(pPrims->vao);

    glBindBuffer(GL_ARRAY_BUFFER, pPrims->vbo[0]);
    glBufferData(GL_ARRAY_BUFFER,  pPrims->MAX_VERTS * pPrims->POS_SIZE_BYTES, NULL, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, pPrims->vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, pPrims->MAX_VERTS * COL_SIZE_BYTES, NULL, GL_DYNAMIC_DRAW);

    CheckOpenGLError("Creating prim buffer");
}

void SaDebugDraw::DeletePrimBuffer(DebugPrims* pPrims)
{
    CheckOpenGLError("Already errored somewhere");

    glDeleteBuffers(2, pPrims->vbo);
    glDeleteVertexArrays(1, &pPrims->vao);

    CheckOpenGLError("Deleting prim buffer");
}

void SaDebugDraw::DrawPrims(DebugPrims* pPrims)
{
    CheckOpenGLError("Already errored somewhere");

    uint32_t shapeType;

    switch(pPrims->SHAPE_TYPE)
    {
        case SHAPE_LINES: shapeType = GL_LINES; break;
        case SHAPE_TRIANGLES: shapeType = GL_TRIANGLES; break;
    }

    glBindVertexArray(pPrims->vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, pPrims->vbo[0]);
    glVertexAttribPointer(SaEffect::POSITION_ATTR, pPrims->VERT_DIMENSIONS, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(SaEffect::POSITION_ATTR);

    glBindBuffer(GL_ARRAY_BUFFER, pPrims->vbo[1]);
    glVertexAttribPointer(SaEffect::COLOUR_ATTR, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(SaEffect::COLOUR_ATTR);

    glDrawArrays(shapeType, 0, pPrims->numVerts);

    glDisableVertexAttribArray(SaEffect::POSITION_ATTR);
    glDisableVertexAttribArray(SaEffect::COLOUR_ATTR);

    CheckOpenGLError("Drawing prims");
}

void SaDebugDraw::AddPrim(DebugPrims* pPrims, const float* pColour, const float* pPos1, const float* pPos2, const float* pPos3)
{
    CheckOpenGLError("Already errored somewhere");

    glBindVertexArray(pPrims->vao);

    glBindBuffer(GL_ARRAY_BUFFER, pPrims->vbo[0]);
    glBufferSubData(GL_ARRAY_BUFFER, (pPrims->numVerts+0) * pPrims->POS_SIZE_BYTES, pPrims->POS_SIZE_BYTES, pPos1);
    glBufferSubData(GL_ARRAY_BUFFER, (pPrims->numVerts+1) * pPrims->POS_SIZE_BYTES, pPrims->POS_SIZE_BYTES, pPos2);
    if (pPrims->SHAPE_VERTS > 2)
        glBufferSubData(GL_ARRAY_BUFFER, (pPrims->numVerts+2) * pPrims->POS_SIZE_BYTES, pPrims->POS_SIZE_BYTES, pPos3);

    glBindBuffer(GL_ARRAY_BUFFER, pPrims->vbo[1]);
    glBufferSubData(GL_ARRAY_BUFFER, (pPrims->numVerts+0) * COL_SIZE_BYTES, COL_SIZE_BYTES, pColour);
    glBufferSubData(GL_ARRAY_BUFFER, (pPrims->numVerts+1) * COL_SIZE_BYTES, COL_SIZE_BYTES, pColour);
    if (pPrims->SHAPE_VERTS > 2)
        glBufferSubData(GL_ARRAY_BUFFER, (pPrims->numVerts+2) * COL_SIZE_BYTES, COL_SIZE_BYTES, pColour);

    CheckOpenGLError("Adding prims");
}
