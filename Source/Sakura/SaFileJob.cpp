/*************************************************************
Sakura Game Framework : SaFileJob.cpp
Author: Darrell Blake
*************************************************************/

#include "SaFileJob.h"
#include "SaDebug.h"

using namespace Sakura;

SaFileJob::SaFileJob()
{
}

SaFileJob::SaFileJob(uint32_t jobIdx, SaCallback<const SaFileJob*> jobFunc, SaCallback<SaFileHandle::EResult, const SaFileHandle*> callback) :
    m_jobIdx(jobIdx),
    m_jobResult(SaFileHandle::RESULT_INVALID),
    m_jobFunc(jobFunc),
    m_callback(callback),
    m_pDestination(NULL),
    m_pSource(NULL),
    m_numBytes(0)
{
}

void SaFileJob::Process()
{
    m_jobFunc(this);
}

uint32_t SaFileJob::GetJobIndex() const
{
    return m_jobIdx;
}

SaCallback<SaFileHandle::EResult, const SaFileHandle*> SaFileJob::GetCallbackFunc() const
{
    return m_callback;
}

uint8_t* SaFileJob::GetDestination() const
{
    return m_pDestination;
}

void SaFileJob::SetDestination(uint8_t* pDestination)
{
    m_pDestination = pDestination;
}

const uint8_t* SaFileJob::GetSource() const
{
    return m_pSource;
}

void SaFileJob::SetSource(const uint8_t* pSource)
{
    m_pSource = pSource;
}

uint32_t SaFileJob::GetNumBytes() const
{
    return m_numBytes;
}

void SaFileJob::SetNumBytes(uint32_t numBytes)
{
    m_numBytes = numBytes;
}
