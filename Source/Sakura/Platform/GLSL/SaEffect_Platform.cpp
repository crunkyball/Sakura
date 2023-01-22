/***************************************************
Sakura Game Framework : SaEffect_Platform.cpp
Author: Darrell Blake

GLSL platform implementation for SaEffect.
***************************************************/

#include "SaEffect_Platform.h"
#include "../../SaTexture.h"
#include "../../SaFile.h"
#include "../../SaEffect.h"
#include PLATFORM_INCLUDE( ../../SA_RENDER_API_DIR/SaTexture_Platform.h )
#include PLATFORM_INCLUDE( ../../SA_RENDER_API_DIR/SaGraphicsAPI.h )
#include <cstdio>
#include "../../SaHash.h"

using namespace Sakura;

const char* SaEffect_Platform::FILE_EXTENSION = ".glsl";

SaEffect_Platform::SaEffect_Platform(SaEffect* pParent) : 
    m_pParent(pParent),
    m_vertexShaderHandle(0),
    m_fragmentShaderHandle(0),
    m_programHandle(0),
    m_uniforms(16, SaHash)
{
}

void SaEffect_Platform::Initialise()
{
}

bool SaEffect_Platform::Load(const uint8_t* pVertexShaderData, const uint8_t* pFragmentShaderData)
{
    int32_t status;

    CheckOpenGLError("Already errored somewhere!");

    //Create the program.
    m_programHandle = glCreateProgram();

    //Load vertex shader.
    m_vertexShaderHandle = glCreateShader(GL_VERTEX_SHADER);

    const char* pFileData = reinterpret_cast<const char*>(pVertexShaderData);
    glShaderSource(m_vertexShaderHandle, 1, &pFileData, NULL);
    glCompileShader(m_vertexShaderHandle);

    glGetShaderiv(m_vertexShaderHandle, GL_COMPILE_STATUS, &status);
    if (status == 0)
    {
        PrintError(m_vertexShaderHandle, "Compiling vertex shader");
        CheckOpenGLError("Compiling vertex shader");
        glDeleteShader(m_vertexShaderHandle);
        return false;
    }

    glAttachShader(m_programHandle, m_vertexShaderHandle);

    //Load fragment shader.
    m_fragmentShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);

    pFileData = reinterpret_cast<const char*>(pFragmentShaderData);
    glShaderSource(m_fragmentShaderHandle, 1, &pFileData, NULL);
    glCompileShader(m_fragmentShaderHandle);

    glGetShaderiv(m_fragmentShaderHandle, GL_COMPILE_STATUS, &status);
    if (status == 0)
    {
        PrintError(m_fragmentShaderHandle, "Compiling fragment shader");
        CheckOpenGLError("Compiling fragment shader");
        glDeleteShader(m_fragmentShaderHandle);
        return false;
    }

    glAttachShader(m_programHandle, m_fragmentShaderHandle);

    //Map the attributes. Important: You must use the constant names in your shaders.
    glBindAttribLocation(m_programHandle, SaEffect::POSITION_ATTR, "aPosition");
    glBindAttribLocation(m_programHandle, SaEffect::COLOUR_ATTR, "aColour");
    glBindAttribLocation(m_programHandle, SaEffect::TEXCOORD0_ATTR, "aTexCoord");
    glBindAttribLocation(m_programHandle, SaEffect::NORMAL_ATTR, "aNormal");

    glLinkProgram(m_programHandle);

    glGetProgramiv(m_programHandle, GL_LINK_STATUS, &status);
    if (status == 0)
    {
        PrintError(m_programHandle, "Linking shader");
        CheckOpenGLError("Linking shader");
        glDeleteProgram(m_programHandle);
        return false;
    }

    int32_t numUniforms;
    int32_t maxUniformName;
    glGetProgramiv(m_programHandle, GL_ACTIVE_UNIFORMS, &numUniforms);
    glGetProgramiv(m_programHandle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxUniformName);

    char* name = static_cast<char*>(alloca(maxUniformName));

    for (uint32_t uniformIdx = 0; uniformIdx < numUniforms; uniformIdx++)
    {
        int32_t size;
        uint32_t type;

        glGetActiveUniform(m_programHandle, uniformIdx, maxUniformName, NULL, &size, &type, name);
        GLint uniformHandle = glGetUniformLocation(m_programHandle, name);

        m_uniforms.Insert(name, uniformHandle);
    }

    if (CheckOpenGLError("Loading shader"))
        return false;

    return true;
}

bool SaEffect_Platform::Unload()
{
    CheckOpenGLError("Already errored somewhere!");

    glDetachShader(m_programHandle, m_vertexShaderHandle);
    glDetachShader(m_programHandle, m_fragmentShaderHandle);
    glDeleteProgram(m_programHandle);

    if (CheckOpenGLError("Deleting shader"))
        return false;

    return true;
}

void SaEffect_Platform::SetIntParameter(SaShaderType shaderType, const char* pParameterName, const int val)
{
    CheckOpenGLError("Already errored somewhere!");

    //We can ignore the shaderType for GLSL.
    int32_t* pUniformHandle = m_uniforms.Find(pParameterName);

    if (pUniformHandle)
    {
        glUniform1i(*pUniformHandle, val);
    }

    CheckOpenGLError("Setting int parameter");
}

void SaEffect_Platform::SetFloatParameter(SaShaderType shaderType, const char* pParameterName, const float val)
{
    CheckOpenGLError("Already errored somewhere!");

    //We can ignore the shaderType for GLSL.
    int32_t* pUniformHandle = m_uniforms.Find(pParameterName);

    if (pUniformHandle)
    {
        glUniform1f(*pUniformHandle, val);
    }

    CheckOpenGLError("Setting float parameter");
}

void SaEffect_Platform::SetMatrixParameter(SaShaderType shaderType, const char* pParameterName, const SakuraMaths::SaMatrix44& rMatrix)
{
    CheckOpenGLError("Already errored somewhere!");

    //We can ignore the shaderType for GLSL.
    int32_t* pUniformHandle = m_uniforms.Find(pParameterName);

    if (pUniformHandle)
    {
        float* pData = (float*)&rMatrix;
        glUniformMatrix4fv(*pUniformHandle, 1, false, pData);
    }

    CheckOpenGLError("Setting matrix parameter");
}

void SaEffect_Platform::SetVectorParameter(SaShaderType shaderType, const char* pParameterName, const SakuraMaths::SaVector3& rVector)
{
    CheckOpenGLError("Already errored somewhere!");

    //We can ignore the shaderType for GLSL.
    int32_t* pUniformHandle = m_uniforms.Find(pParameterName);

    if (pUniformHandle)
    {
        float* pData = (float*)&rVector;
        glUniform3fv(*pUniformHandle, 1, pData);
    }

    CheckOpenGLError("Setting vector parameter");
}

void SaEffect_Platform::SetColourParameter(SaShaderType shaderType, const char* pParameterName, const SaColour& rColour)
{
    CheckOpenGLError("Already errored somewhere!");

    //We can ignore the shaderType for GLSL.
    int32_t* pUniformHandle = m_uniforms.Find(pParameterName);

    if (pUniformHandle)
    {
        float* pData = (float*)&rColour;
        glUniform4fv(*pUniformHandle, 1, pData);
    }

    CheckOpenGLError("Setting colour parameter");
}

void SaEffect_Platform::SetTextureParameter(SaShaderType shaderType, const char* pParameterName, const SaTexture* pTexture)
{
    CheckOpenGLError("Already errored somewhere!");

    //We can ignore the shaderType for GLSL.
    int32_t* pUniformHandle = m_uniforms.Find(pParameterName);
    
    if (pUniformHandle)
    {
        const SaTexture_Platform& rPlatformTexture = pTexture->GetPlatformTexture();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, rPlatformTexture.GetHandle());
        glUniform1i(*pUniformHandle, 0);
    }

    CheckOpenGLError("Setting texture parameter");
}

void SaEffect_Platform::Enable()
{
    CheckOpenGLError("Already errored somewhere!");
    glUseProgram(m_programHandle);
    CheckOpenGLError("Enabling shader");
}

void SaEffect_Platform::Disable()
{
}

void SaEffect_Platform::PrintError(int32_t handle, const char* reason)
{
    int32_t logLength = 0;
    glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &logLength);

    if (logLength > 1)
    {
        char* pLog = new char[logLength];

        glGetShaderInfoLog(handle, logLength, &logLength, pLog);
        SA_PRINTF("ERROR: %s:\n%s", reason, pLog);

        delete[] pLog;
    }

    SA_FAIL(reason);
}
