/*************************************************************
Sakura Game Framework : SaSprite.cpp
Author: Darrell Blake
*************************************************************/

#include "SaSprite.h"
#include "SaRenderState.h"
#include <SakuraMaths/SaMatrix44.h>
#include "SaDebug.h"
#include "SaRender.h"

using namespace Sakura;
using namespace SakuraMaths;

const SaVector2 SaSprite::ms_verts[4] = { SaVector2(0.0f, 0.0f), 
                                    SaVector2(0.0f, 1.0f), 
                                    SaVector2(1.0f, 0.0f),
                                    SaVector2(1.0f, 1.0f) };
const SaVector2 SaSprite::ms_texCoords[4] = { SaVector2(0.0f, 0.0f), 
                                        SaVector2(0.0f, 1.0f), 
                                        SaVector2(1.0f, 0.0f),
                                        SaVector2(1.0f, 1.0f) };
const uint16_t SaSprite::ms_indices[4] = { 0, 1, 2, 3 };

SaSprite::SaSprite() :
    m_position(SaVector2::ALL_ZERO),
    m_scale(SaVector2::ALL_ONE),
    m_pTexture(NULL),
    m_pSpriteEffect(NULL)
{
    m_colour = SaColour(1.0f, 1.0f, 1.0f, 1.0f);
}

SaSprite::~SaSprite()
{
    m_platformSprite.Release();
}

void SaSprite::Create(const SaTexture* pTexture, SaEffect* pEffect)
{
    m_pSpriteEffect = pEffect;
    m_pTexture = pTexture;

    SaRenderJob job(BIND_MEMBER_FUNC(&SaSprite::RenderThread_Create, this));
    SaRender::AddRenderJob(job);
}

void SaSprite::SetColour(const SaColour& rColour)
{
    m_colour = rColour;
}

void SaSprite::SetPosition(const SaVector2& rPosition)
{
    m_position = rPosition;
}

void SaSprite::SetScale(const SaVector2& rScale)
{
    m_scale = rScale;
}

void SaSprite::Render()
{
    SA_ASSERT(m_pSpriteEffect, "Sprite not initialised.");

    if (!m_pSpriteEffect)
        return;
    
    uint32_t width, height;
    width = height = 0;
    m_pTexture->GetDimensions(width, height);

    SaMatrix44 translationMat = SaMatrix44::CreateTranslation(m_position.GetX(), m_position.GetY(), 0.0f);
    SaMatrix44 scaleMat = SaMatrix44::CreateScale(width * m_scale.GetX(), height * m_scale.GetY(), 0.0f);
    SaMatrix44 transformMat = translationMat * scaleMat;

    m_pSpriteEffect->Enable();

    m_pSpriteEffect->SetMatrixParameter(VERTEX_SHADER, "modelMatrix", transformMat);
    m_pSpriteEffect->SetMatrixParameter(VERTEX_SHADER, "projectionMatrix", SaRenderState::Get2DProjectionMatrix());
    m_pSpriteEffect->SetColourParameter(FRAGMENT_SHADER, "colour", m_colour);
    m_pSpriteEffect->SetTextureParameter(FRAGMENT_SHADER, "texture", m_pTexture);

    SaRenderJob job(BIND_MEMBER_FUNC(&SaSprite::RenderThread_Render, this));
    SaRender::AddRenderFrameJob(job);

    m_pSpriteEffect->Disable();
}

void SaSprite::RenderThread_Create(const SaRenderJob* pJob)
{
    m_platformSprite.Create();
}

void SaSprite::RenderThread_Render(const SaRenderJob* pJob)
{
    m_platformSprite.Render();
}
