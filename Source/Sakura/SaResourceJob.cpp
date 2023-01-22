/*************************************************************
Sakura Game Framework : SaResourceJob.cpp
Author: Darrell Blake
*************************************************************/

#include "SaResourceJob.h"

using namespace Sakura;

SaResourceJob::SaResourceJob() :
    m_resourceHash(0),
    m_jobFunc(NULL),
    m_pFileName(NULL)
{
}

SaResourceJob::SaResourceJob(uint32_t resourceHash, ProcessJobFunc processJobFunc) :
    m_resourceHash(resourceHash),
    m_jobFunc(processJobFunc),
    m_pFileName(NULL)
{
}

void SaResourceJob::Process()
{
    if (m_jobFunc)
        m_jobFunc(this);
}
