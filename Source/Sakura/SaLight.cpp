/*************************************************************
Sakura Game Framework : SaLight.cpp
Author: Darrell Blake
*************************************************************/

#include "SaLight.h"
#include "SaDebugDraw.h"

using namespace Sakura;
using namespace SakuraMaths;

SaLight::SaLight() :
    m_colour(SaColour::WHITE)
{
}

SaLight::~SaLight()
{
}

void SaLight::Initialise(const SaColour& rColour)
{
    m_colour = rColour;
}

void SaLight::Update(uint32_t dt)
{
    SaGameObject::Update(dt);
}

#ifdef SA_BUILD_DEBUG
void SaLight::DebugRender()
{
    float lineLength = 0.2f;
    SaDebugDraw::DrawLine3D(GetPosition() - SaVector3::X_AXIS * lineLength, GetPosition() + SaVector3::X_AXIS * lineLength, m_colour);
    SaDebugDraw::DrawLine3D(GetPosition() - SaVector3::Y_AXIS * lineLength, GetPosition() + SaVector3::Y_AXIS * lineLength, m_colour);
    SaDebugDraw::DrawLine3D(GetPosition() - (SaVector3::X_AXIS - SaVector3::Y_AXIS).GetNormalised() * lineLength, GetPosition() + (SaVector3::X_AXIS - SaVector3::Y_AXIS).GetNormalised() * lineLength, m_colour);
    SaDebugDraw::DrawLine3D(GetPosition() - (-SaVector3::X_AXIS - SaVector3::Y_AXIS).GetNormalised() * lineLength, GetPosition() + (-SaVector3::X_AXIS - SaVector3::Y_AXIS).GetNormalised() * lineLength, m_colour);
}
#endif

const SaColour& SaLight::GetColour() const
{
    return m_colour;
}

void SaLight::SetColour(const SaColour& rColour)
{
    m_colour = rColour;
}
