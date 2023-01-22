/***************************************************
Sakura Game Framework : SaTexture_Platform.cpp
Author: Darrell Blake

OpenGL ES platform implementation for SaTexture.
***************************************************/

#include "SaTexture_Platform.h"
#include "../../SaTexture.h"
#include "SaGraphicsAPI.h"
#include "../../SaDebug.h"

using namespace Sakura;

SaTexture_Platform::SaTexture_Platform(SaTexture* pParent) :
    m_pParent(pParent),
    m_handle(0)
{
}

bool SaTexture_Platform::Load(uint8_t* pData)
{
    CheckOpenGLError("Already errored somewhere!");

    uint32_t textureFormat = m_pParent->m_bitDepth == 4 ? GL_RGBA : GL_RGB;

    glGenTextures(1, &m_handle);
    glBindTexture(GL_TEXTURE_2D, m_handle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 textureFormat,
                 m_pParent->m_width,
                 m_pParent->m_height,
                 0,
                 textureFormat,
                 GL_UNSIGNED_BYTE,
                 pData);

    if (CheckOpenGLError("Loading texture"))
        return false;

    return true;
}

bool SaTexture_Platform::Unload()
{
    CheckOpenGLError("Already errored somewhere!");

    glDeleteTextures(1, &m_handle);

    if (CheckOpenGLError("Unloading texture"))
        return false;

    return true;
}

const uint32_t SaTexture_Platform::GetHandle() const
{
    return m_handle;
}
