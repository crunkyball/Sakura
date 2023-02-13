/*************************************************************
Sakura Game Framework : SaInputComponentFreeCam.cpp
Author: Darrell Blake
*************************************************************/

#include "SaInputComponentFreeCam.h"
#include "SaCamera.h"
#include <SakuraMaths/SaMatrix33.h>
#include "SaInputManager.h"

using namespace Sakura;
using namespace SakuraMaths;

SaInputComponentFreeCam::SaInputComponentFreeCam()
{
}

SaInputComponentFreeCam::~SaInputComponentFreeCam()
{
}

void SaInputComponentFreeCam::Update(uint32_t dt)
{
    float fSpeed = 0.01f;

    float xTrans, zTrans;
    xTrans = zTrans = 0.0f;

    float pitch, yaw;
    pitch = yaw = 0.0f;

    const SaKeyboard& rKeyboard = SaInputManager::GetKeyboard();

    if (rKeyboard.IsKeyDown(SA_KEY_W))
        zTrans = 0.5f*fSpeed*dt;
    if (rKeyboard.IsKeyDown(SA_KEY_S))
        zTrans = -0.5f*fSpeed*dt;
    if (rKeyboard.IsKeyDown(SA_KEY_A))
        xTrans = 0.5f*fSpeed*dt;
    if (rKeyboard.IsKeyDown(SA_KEY_D))
        xTrans = -0.5f*fSpeed*dt;

    if (rKeyboard.IsKeyDown(SA_KEY_L))
        yaw = -0.1f*fSpeed*dt;
    if (rKeyboard.IsKeyDown(SA_KEY_J))
        yaw = 0.1f*fSpeed*dt;
    if (rKeyboard.IsKeyDown(SA_KEY_I))
        pitch = 0.1f*fSpeed*dt;
    if (rKeyboard.IsKeyDown(SA_KEY_K))
        pitch = -0.1f*fSpeed*dt;

    SaCamera* pCamera = static_cast<SaCamera*>(m_pParent);

    //Update camera rotation.
    const SaMatrix33& rCamRot = pCamera->GetRotation();

    const SaVector3& rLeft = rCamRot.GetColumn0();
    //const SaVector3& rUp = rCamRot.GetColumn1();
    const SaVector3& rForward = rCamRot.GetColumn2();

    SaMatrix33 pitchRot = SaMatrix33::CreateXRotation(pitch);
    SaMatrix33 yawRot = SaMatrix33::CreateYRotation(yaw);

    SaMatrix33 newRot = yawRot * rCamRot * pitchRot;
    pCamera->SetRotation(newRot);


    //Update camera position.
    const SaVector3& rCamPos = pCamera->GetPosition();

    SaVector3 newPos = rCamPos + rLeft * xTrans + rForward * zTrans;
    pCamera->SetPosition(newPos);
}
