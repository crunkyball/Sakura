/*************************************************************
Sakura Game Framework : SaScene.cpp
Author: Darrell Blake
*************************************************************/

#include "SaScene.h"
#include "SaCamera.h"

using namespace Sakura;

SaScene::SaScene() :
    m_bDrawGrid(false),
    m_bDrawAxes(false)
{
}

SaScene::~SaScene()
{
}

void SaScene::Update(uint32_t dt)
{
}

void SaScene::Render()
{
    if (m_bDrawGrid)
    {

    }

    if (m_bDrawAxes)
    {

    }
}
