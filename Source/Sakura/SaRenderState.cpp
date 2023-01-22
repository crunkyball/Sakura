/*************************************************************
Sakura Game Framework : SaRenderState.cpp
Author: Darrell Blake
*************************************************************/

#include "SaRenderState.h"

using namespace Sakura;
using namespace SakuraMaths;

SaMatrix44 SaRenderState::m_viewMatrix = SaMatrix44::IDENTITY;
SaMatrix44 SaRenderState::m_projectionMatrix = SaMatrix44::IDENTITY;

SaMatrix44 SaRenderState::m_2DprojectionMatrix = SaMatrix44::IDENTITY;
