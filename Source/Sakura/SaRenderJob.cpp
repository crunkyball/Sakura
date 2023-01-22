/*************************************************************
Sakura Game Framework : SaRenderJob.cpp
Author: Darrell Blake
*************************************************************/

#include "SaRenderJob.h"
#include <cstring>

using namespace Sakura;

SaRenderJob::SaRenderJob() :
    m_enable(false)
{
}

SaRenderJob::SaRenderJob(SaCallback<const SaRenderJob*> jobFunc) :
    m_jobFunc(jobFunc),
    m_enable(false)
{
}

void SaRenderJob::Process()
{
    m_jobFunc(this);
}
