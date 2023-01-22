/*************************************************************
Sakura Game Framework : SaModel_Platform.cpp
Author: Darrell Blake

OpenGL ES platform implementation for SaModel.
*************************************************************/

#include "SaModel_Platform.h"
#include "../../SaModel.h"

using namespace Sakura;
using namespace SakuraMaths;

SaModel_Platform::SaModel_Platform(SaModel* pParent) : 
    m_pParent(pParent)
{
}

bool SaModel_Platform::Load()
{
    return false;
}

bool SaModel_Platform::Unload()
{
    return false;
}

void SaModel_Platform::Render()
{
}
