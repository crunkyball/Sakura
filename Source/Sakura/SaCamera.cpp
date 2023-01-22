/*************************************************************
Sakura Game Framework : SaCamera.cpp
Author: Darrell Blake
*************************************************************/

#include "SaCamera.h"
#include "SaRenderState.h"
#include "SaInputComponentFreecam.h"

using namespace Sakura;
using namespace SakuraMaths;

SaCamera::SaCamera() : 
    m_projection(SaMatrix44::IDENTITY),
    m_view(SaMatrix44::IDENTITY)
{
}

SaCamera::~SaCamera()
{
}

void SaCamera::Initialise(float fAspectRatio, float fov, float fNearPlane, float fFarPlane)
{
    m_projection = SaMatrix44::CreatePerspectiveProjection(fov, fAspectRatio, fNearPlane, fFarPlane);
    m_view = SaMatrix44(SaVector4::X_AXIS,
                        SaVector4::Y_AXIS,
                        SaVector4::Z_AXIS,
                        SaVector4(-SaVector3::Z_AXIS, 1.0f));
}

void SaCamera::Update(uint32_t dt)
{
    SaGameObject::Update(dt);

    const SaVector3& rUp = GetRotation().GetColumn1();
    const SaVector3& rForward = GetRotation().GetColumn2();

    m_view = SaMatrix44::CreateLookAt(GetPosition(), GetPosition() + rForward, rUp);
}

const SaMatrix44& SaCamera::GetProjectionMatrix() const
{
    return m_projection;
}

const SaMatrix44& SaCamera::GetViewMatrix() const
{
    return m_view;
}
