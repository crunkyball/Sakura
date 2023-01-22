/*************************************************************
Sakura Game Framework : SaInputComponent.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_INPUT_COMPONENT_H
#define _SA_INPUT_COMPONENT_H

#include "SaCore.h"

namespace Sakura
{
    class SaGameObject;

    class SaInputComponent
    {
    public:
        SaInputComponent();
        virtual ~SaInputComponent();

        virtual void Update(uint32_t dt);

        void SetParent(SaGameObject* pParent);

    protected:
        SaGameObject* m_pParent;
    };
}

#endif  //_SA_INPUT_COMPONENT_H
