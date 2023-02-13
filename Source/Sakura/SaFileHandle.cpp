/*************************************************************
Sakura Game Framework : SaFileHandle.cpp
Author: Darrell Blake
*************************************************************/

#include "SaFileHandle.h"
#include "SaFileJob.h"
#include "SaFile.h"

using namespace Sakura;

SaFileHandle::SaFileHandle(const char* pFileName) :
    m_pFileName(pFileName),
    m_openFlags(0),
    m_pHandle(NULL),
    m_fileSize(0),
    m_jobCount(0),
    m_blockJobIdx(0),
    m_blockJobResult(RESULT_INVALID)
{
}

SaFileJob SaFileHandle::CreateJob(SaCallback<const SaFileJob*> jobFunc, SaCallback<EResult, const SaFileHandle*> callback)
{
    uint32_t jobIdx = ++m_jobCount;
    SaFileJob job(jobIdx, jobFunc, callback);
    return job;
}

SaFileHandle::EResult SaFileHandle::Open(uint32_t openFlags, bool blockUntilDone, SaCallback<EResult, const SaFileHandle*> callback)
{
    m_openFlags = openFlags;

    SaFileJob job = CreateJob(BIND_MEMBER_FUNC(&SaFileHandle::FileThread_Open, this), callback);

    return AddJob(job, blockUntilDone);
}

SaFileHandle::EResult SaFileHandle::Read(uint8_t* pDestination, uint32_t numBytes, bool blockUntilDone, SaCallback<EResult, const SaFileHandle*> callback)
{
    SA_ASSERT(m_openFlags & FLAG_READ, "Invalid operation on this handle.");

    SaFileJob job = CreateJob(BIND_MEMBER_FUNC(&SaFileHandle::FileThread_Read, this), callback);
    job.SetDestination(pDestination);
    job.SetNumBytes(numBytes);

    return AddJob(job, blockUntilDone);
}

SaFileHandle::EResult SaFileHandle::Write(const uint8_t* pSource, uint32_t numBytes, bool blockUntilDone, SaCallback<EResult, const SaFileHandle*> callback)
{
    SA_ASSERT(m_openFlags & FLAG_WRITE, "Invalid operation on this handle.");

    SaFileJob job = CreateJob(BIND_MEMBER_FUNC(&SaFileHandle::FileThread_Write, this), callback);
    job.SetSource(pSource);
    job.SetNumBytes(numBytes);

    return AddJob(job, blockUntilDone);
}

SaFileHandle::EResult SaFileHandle::Seek(uint32_t position, bool blockUntilDone, SaCallback<EResult, const SaFileHandle*> callback)
{
    SaFileJob job = CreateJob(BIND_MEMBER_FUNC(&SaFileHandle::FileThread_Seek, this), callback);
    job.SetNumBytes(position);

    return AddJob(job, blockUntilDone);
}

SaFileHandle::EResult SaFileHandle::Close(bool blockUntilDone, SaCallback<EResult, const SaFileHandle*> callback)
{
    SaFileJob job = CreateJob(BIND_MEMBER_FUNC(&SaFileHandle::FileThread_Close, this), callback);
    return AddJob(job, blockUntilDone);
}

uint32_t SaFileHandle::GetSize() const
{
    return m_fileSize;
}

SaFileHandle::EResult SaFileHandle::AddJob(const SaFileJob& rJob, bool block)
{
    if (block)
    {
        m_blockMutex.Lock();
        SA_ASSERT(m_blockJobIdx == 0, "This handle is already blocking!");
        m_blockJobIdx = rJob.GetJobIndex();
        m_blockMutex.Unlock();
    }

    SaFile::AddJob(rJob);

    if (!block)
    {
        return RESULT_PROCESSING;
    }

    return WaitForJob();
}

SaFileHandle::EResult SaFileHandle::WaitForJob()
{
    EResult result = RESULT_FAILED;

    m_blockMutex.Lock();

    while (m_blockJobResult != RESULT_SUCCEEDED && m_blockJobResult != RESULT_FAILED)
    {
        m_blockCondition.Wait(m_blockMutex);
    }

    result = m_blockJobResult;
    m_blockJobResult = RESULT_INVALID;
    m_blockJobIdx = 0;

    m_blockMutex.Unlock();

    return result;
}

void SaFileHandle::JobDone(const SaFileJob* pJob, EResult result)
{
    SaCallback<SaFileHandle::EResult, const SaFileHandle*> callbackFunc = pJob->GetCallbackFunc();
    callbackFunc(result, this);

    m_blockMutex.Lock();

    if (m_blockJobIdx == pJob->GetJobIndex())
    {
        m_blockJobResult = result;
        m_blockCondition.Signal();
    }

    m_blockMutex.Unlock();
}

void SaFileHandle::FileThread_Open(const SaFileJob* pJob)
{
    const char* flags = "";

    if (m_openFlags & FLAG_READ)
        flags = "rb";
    if (m_openFlags & FLAG_WRITE)
        flags = "rb+";
    if (m_openFlags & FLAG_CREATE)
        flags = "wb+";

    fopen_s(&m_pHandle, m_pFileName, flags);

    EResult result = RESULT_FAILED;

    if (m_pHandle)
    {
        int32_t pos = ftell(m_pHandle);

        fseek(m_pHandle, 0, SEEK_END);
        m_fileSize = ftell(m_pHandle);
        fseek(m_pHandle, pos, SEEK_SET);

        result = RESULT_SUCCEEDED;
    }

    JobDone(pJob, result);
}

void SaFileHandle::FileThread_Read(const SaFileJob* pJob)
{
    EResult result = RESULT_FAILED;

    uint32_t bytesRead = static_cast<uint32_t>(fread(pJob->GetDestination(), 1, pJob->GetNumBytes(), m_pHandle));

    if (bytesRead == pJob->GetNumBytes())
    {
        result = RESULT_SUCCEEDED;
    }

    JobDone(pJob, result);
}

void SaFileHandle::FileThread_Write(const SaFileJob* pJob)
{
    EResult result = RESULT_FAILED;

    uint32_t bytesWritten = static_cast<uint32_t>(fwrite(pJob->GetSource(), 1, pJob->GetNumBytes(), m_pHandle));

    if (bytesWritten == pJob->GetNumBytes())
    {
        result = RESULT_SUCCEEDED;
    }

    JobDone(pJob, result);
}

void SaFileHandle::FileThread_Seek(const SaFileJob* pJob)
{
    EResult result = RESULT_FAILED;

    if (fseek(m_pHandle, pJob->GetNumBytes(), SEEK_SET) == 0)
    {
        result = RESULT_SUCCEEDED;
    }

    JobDone(pJob, result);
}

void SaFileHandle::FileThread_Close(const SaFileJob* pJob)
{
    EResult result = RESULT_FAILED;

    if (fclose(m_pHandle) == 0)
    {
        result = RESULT_SUCCEEDED;
    }

    JobDone(pJob, result);
}
