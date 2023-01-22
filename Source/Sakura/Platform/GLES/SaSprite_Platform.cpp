/***************************************************
Sakura Game Framework : SaSprite_Platform.cpp
Author: Darrell Blake

OpenGL ES platform implementation for SaSprite.
***************************************************/

#include "SaSprite_Platform.h"
#include <SakuraMaths/SaVector2.h>
#include "../../SaEffect.h"
#include "../../SaSprite.h"
#include "SaGraphicsAPI.h"

using namespace Sakura;
using namespace SakuraMaths;

SaSprite_Platform::SaSprite_Platform()
{
}

void SaSprite_Platform::Create()
{
    glGenBuffers(2, m_vbo);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(SaVector2), SaSprite::ms_verts, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(SaVector2), SaSprite::ms_texCoords, GL_STATIC_DRAW);
}

void SaSprite_Platform::Release()
{
    glDeleteBuffers(2, m_vbo);
}

void SaSprite_Platform::Render()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo[0]);
    glVertexAttribPointer(SaEffect::POSITION_ATTR, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(SaEffect::POSITION_ATTR);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo[1]);
    glVertexAttribPointer(SaEffect::TEXCOORD0_ATTR, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(SaEffect::TEXCOORD0_ATTR);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisableVertexAttribArray(SaEffect::TEXCOORD0_ATTR);
    glDisableVertexAttribArray(SaEffect::POSITION_ATTR);
}
