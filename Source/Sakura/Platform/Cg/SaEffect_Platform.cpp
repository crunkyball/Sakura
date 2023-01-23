/*************************************************************
Sakura Game Framework : SaEffect_Platform.cpp
Author: Darrell Blake

Cg platform implementation for SaEffect.
*************************************************************/

#include "SaEffect_Platform.h"
#include <SakuraMaths/SaMatrix44.h>
#include "../../SaTexture.h"
#include "../../SaFile.h"
#include "../../SaHash.h"
#include <cstdio>
#include PLATFORM_INCLUDE( ../../SA_RENDER_API_DIR/SaTexture_Platform.h)

using namespace Sakura;
using namespace SakuraMaths;

const char* SaEffect_Platform::FILE_EXTENSION = ".cg";

CGcontext SaEffect_Platform::ms_cgContext;
CGprofile SaEffect_Platform::ms_vertexProfile;
CGprofile SaEffect_Platform::ms_fragmentProfile;

SaEffect_Platform::SaEffect_Platform(SaEffect* pParent) :
    m_pParent(pParent),
    m_vertexParameters(32, SaHash),
    m_fragmentParameters(32, SaHash)
{
}

bool SaEffect_Platform::Initialise()
{
    SA_ASSERT(ms_cgContext == NULL, "Cg already initialised.");

    if (ms_cgContext != NULL)
        return false;

    ms_cgContext = cgCreateContext();

    if (CheckCgError())
        return false;

    ms_vertexProfile = cgGLGetLatestProfile(CG_GL_VERTEX);
    if (CheckCgError())
        return false;

    cgGLSetOptimalOptions(ms_vertexProfile);
    if (CheckCgError())
        return false;

    ms_fragmentProfile = cgGLGetLatestProfile(CG_GL_FRAGMENT);
    if (CheckCgError())
        return false;

    cgGLSetOptimalOptions(ms_fragmentProfile);
    if (CheckCgError())
        return false;

    cgGLSetDebugMode(CG_FALSE);
    cgSetParameterSettingMode(ms_cgContext, CG_IMMEDIATE_PARAMETER_SETTING);

    return true;
}

void SaEffect_Platform::PopulateParams(CGparameter param, SaHashTable<const char*, CGparameter>& paramTable)
{
    while (param)
    {
        CGtype type = cgGetParameterType(param);

        if (type == CG_STRUCT)
        {
            CGparameter structParam = cgGetFirstStructParameter(param);
            const char* paramName = cgGetParameterName(structParam);
            PopulateParams(structParam, paramTable);
        }
        else if (type == CG_ARRAY)
        {
            uint32_t dimensions = cgGetArrayDimension(param);

            for (uint32_t d = 0; d < dimensions; d++)
            {
                uint32_t size = cgGetArraySize(param, d);

                for (uint32_t i = 0; i < size; i++)
                {
                    CGparameter arrayParam = cgGetArrayParameter(param, (d+1)*i);
                    PopulateParams(arrayParam, paramTable);
                }
            }
        }
        else
        {
            const char* paramName = cgGetParameterName(param);
            paramTable.Insert(paramName, param);
        }

        param = cgGetNextParameter(param);
    }
}

bool SaEffect_Platform::Load(const uint8_t* pVertexShaderData, const uint8_t* pFragmentShaderData)
{
    SA_ASSERT(ms_cgContext > 0, "Cg not initialised?");

    if (ms_cgContext)
    {
        //Load vertex shader.
        m_vertexProgram = cgCreateProgram(ms_cgContext, CG_SOURCE, reinterpret_cast<const char*>(pVertexShaderData), ms_vertexProfile, "main", NULL);

        if (CheckCgError())
            return false;

        cgGLLoadProgram(m_vertexProgram);
        if (CheckCgError())
            return false;

        //Get parameters.
        CGparameter param = cgGetFirstParameter(m_vertexProgram, CG_PROGRAM);
        PopulateParams(param, m_vertexParameters);

        //Load fragment shader.
        m_fragmentProgram = cgCreateProgram(ms_cgContext, CG_SOURCE, reinterpret_cast<const char*>(pFragmentShaderData), ms_fragmentProfile, "main", NULL);
        
        if (CheckCgError())
            return false;
        
        cgGLLoadProgram(m_fragmentProgram);
        if (CheckCgError())
            return false;

        //Get parameters.
        param = cgGetFirstParameter(m_fragmentProgram, CG_PROGRAM);
        PopulateParams(param, m_fragmentParameters);

        return true;
    }

    return false;
}

bool SaEffect_Platform::Unload()
{
    cgDestroyProgram(m_vertexProgram);
    cgDestroyProgram(m_fragmentProgram);

    if (CheckCgError())
        return false;

    return true;
}

void SaEffect_Platform::SetIntParameter(SaShaderType shaderType, const char* pParameterName, const int val)
{
    CGparameter* pParam = GetParameter(shaderType, pParameterName);

    SA_ASSERT(pParam, "Invalid parameter.");

    if (pParam)
    {
        cgSetParameter1i(*pParam, val);
        CheckCgError();
    }
}

void SaEffect_Platform::SetFloatParameter(SaShaderType shaderType, const char* pParameterName, const float val)
{
    CGparameter* pParam = GetParameter(shaderType, pParameterName);

    SA_ASSERT(pParam, "Invalid parameter.");
    
    if (pParam)
    {
        cgGLSetParameter1f(*pParam, val);
        CheckCgError();
    }
}

void SaEffect_Platform::SetVectorParameter(SaShaderType shaderType, const char* pParameterName, const SakuraMaths::SaVector3& rVector)
{
    CGparameter* pParam = GetParameter(shaderType, pParameterName);

    SA_ASSERT(pParam, "Invalid parameter.");

    if (pParam)
    {
        cgGLSetParameter3fv(*pParam, (const float*)&rVector);
        CheckCgError();
    }
}

void SaEffect_Platform::SetMatrixParameter(SaShaderType shaderType, const char* pParameterName, const SaMatrix44& rMatrix)
{
    CGparameter* pParam = GetParameter(shaderType, pParameterName);

    SA_ASSERT(pParam, "Invalid parameter.");

    if (pParam)
    {
        float* pData = (float*)&rMatrix;
        cgSetMatrixParameterfc(*pParam, pData);
        CheckCgError();
    }
}

void SaEffect_Platform::SetColourParameter(SaShaderType shaderType, const char* pParameterName, const SaColour& rColour)
{
    CGparameter* pParam = GetParameter(shaderType, pParameterName);

    SA_ASSERT(pParam, "Invalid parameter.");

    if (pParam)
    {
        cgGLSetParameter4fv(*pParam, (const float*)&rColour);
        CheckCgError();
    }
}

void SaEffect_Platform::SetTextureParameter(SaShaderType shaderType, const char* pParameterName, const SaTexture* pTexture)
{
    CGparameter* pParam = GetParameter(shaderType, pParameterName);

    SA_ASSERT(pParam, "Invalid parameter.");

    if (pParam)
    {
        const SaTexture_Platform& rPlatformTexture = pTexture->GetPlatformTexture();

        cgGLSetTextureParameter(*pParam, rPlatformTexture.GetHandle());
        cgGLEnableTextureParameter(*pParam);
        CheckCgError();
    }
}

CGparameter* SaEffect_Platform::GetParameter(SaShaderType shaderType, const char* pParameterName)
{
    CGparameter* pParameter = NULL;

    if (shaderType == VERTEX_SHADER)
        pParameter = m_vertexParameters.Find(pParameterName);
    else if (shaderType == FRAGMENT_SHADER)
        pParameter = m_fragmentParameters.Find(pParameterName);

    return pParameter;
}

void SaEffect_Platform::Enable()
{
    cgGLEnableProfile(ms_vertexProfile);
    cgGLBindProgram(m_vertexProgram);
    CheckCgError();

    cgGLEnableProfile(ms_fragmentProfile);
    cgGLBindProgram(m_fragmentProgram);
    CheckCgError();
}

void SaEffect_Platform::Disable()
{
    cgGLUnbindProgram(ms_vertexProfile);
    cgGLDisableProfile(ms_vertexProfile);
    CheckCgError();

    cgGLUnbindProgram(ms_fragmentProfile);
    cgGLDisableProfile(ms_fragmentProfile);
    CheckCgError();
}

bool SaEffect_Platform::CheckCgError()
{
    CGerror error;
    const char* sError = cgGetLastErrorString(&error);

    if (error != CG_NO_ERROR)
    {
        SA_PRINTF("Cg Error: %s\n", sError);

        if (error == CG_COMPILER_ERROR)
            SA_PRINTF("%s\n", cgGetLastListing(ms_cgContext));

        SA_FAIL("Cg Error!");
        return true;
    }

    return false;
}
