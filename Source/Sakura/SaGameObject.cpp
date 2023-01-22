/*************************************************************
Sakura Game Framework : SaGameObject.cpp
Author: Darrell Blake
*************************************************************/

#include "SaGameObject.h"
#include "SaInputComponent.h"
#include "SaDebug.h"

using namespace Sakura;
using namespace SakuraMaths;

SaGameObject::SaGameObject() :
    m_position(SaVector3::ALL_ZERO),
    m_rotation(SaMatrix33::IDENTITY),
    m_pInputComponent(NULL)
{
}

SaGameObject::~SaGameObject()
{
}

void SaGameObject::Update(uint32_t dt)
{
    if (m_pInputComponent)
        m_pInputComponent->Update(dt);
}

const SaVector3& SaGameObject::GetPosition() const
{
    return m_position;
}

void SaGameObject::SetPosition(const SaVector3& rPosition)
{
    m_position = rPosition;
}

const SaMatrix33& SaGameObject::GetRotation() const
{
    return m_rotation;
}

void SaGameObject::SetRotation(const SaMatrix33& rRotation)
{
    m_rotation = rRotation;
}

void SaGameObject::SetInputComponent(Sakura::SaInputComponent *pInputComponent)
{
    SA_ASSERT(m_pInputComponent == NULL, "Input component already set?");
    m_pInputComponent = pInputComponent;
    m_pInputComponent->SetParent(this);
}
