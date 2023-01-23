/*************************************************************
Sakura Game Framework : SaCamera.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_CAMERA_H
#define _SA_CAMERA_H

#include "SaCore.h"
#include "SaGameObject.h"
#include <SakuraMaths/SaMatrix44.h>
#include <SakuraMaths/SaMatrix33.h>

namespace Sakura
{
    class SaCamera : public SaGameObject
    {
    public:
        SaCamera();
        virtual ~SaCamera();

        void Initialise(float fAspectRatio, float fov = 45.0f, float fNearPlane = 0.1f, float fFarPlane = 1000.0f);

        virtual void Update(uint32_t dt) override;

        const SakuraMaths::SaMatrix44& GetProjectionMatrix() const;
        const SakuraMaths::SaMatrix44& GetViewMatrix() const;

    private:
        SakuraMaths::SaMatrix44 m_projection;
        SakuraMaths::SaMatrix44 m_view;
    };
}

#endif  //_SA_CAMERA_H
