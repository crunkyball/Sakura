/*************************************************************
Sakura Game Framework : SaInputComponent.cpp
Author: Darrell Blake
*************************************************************/

#include "SaInputComponent.h"

using namespace Sakura;

SaInputComponent::SaInputComponent()
{
}

SaInputComponent::~SaInputComponent()
{
}

void SaInputComponent::Update(uint32_t dt)
{
}

void SaInputComponent::SetParent(SaGameObject* pParent)
{
    m_pParent = pParent;
}
