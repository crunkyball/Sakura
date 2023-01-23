/*************************************************************
Sakura Game Framework : SaInputComponentFreeCam.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_INPUT_COMPONENT_FREE_CSA_H
#define _SA_INPUT_COMPONENT_FREE_CSA_H

#include "SaCore.h"

#include "SaInputComponent.h"

namespace Sakura
{
	class SaCamera;

    class SaInputComponentFreeCam : public SaInputComponent
    {
    public:
        SaInputComponentFreeCam();
        virtual ~SaInputComponentFreeCam();

        virtual void Update(uint32_t dt) override;
    };
}

#endif  //_SA_INPUT_COMPONENT_FREE_CSA_H
