/*************************************************************
Sakura Game Framework : SaGameObject.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_GAME_OBJECT_H
#define _SA_GAME_OBJECT_H

#include "SaCore.h"
#include <SakuraMaths/SaMatrix33.h>

namespace Sakura
{
    class SaInputComponent;

    class SaGameObject
    {
    public:
        SaGameObject();
        virtual ~SaGameObject();

        virtual void Update(uint32_t dt);

        const SakuraMaths::SaVector3& GetPosition() const;
        void SetPosition(const SakuraMaths::SaVector3& rPosition);

        const SakuraMaths::SaMatrix33& GetRotation() const;
        void SetRotation(const SakuraMaths::SaMatrix33& rRotation);

        void SetInputComponent(SaInputComponent* pInputComponent);

    private:
        SakuraMaths::SaVector3 m_position;
        SakuraMaths::SaMatrix33 m_rotation;

        SaInputComponent* m_pInputComponent;
    };
}

#endif  //_SA_GAME_OBJECT_H
