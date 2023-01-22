/*************************************************************
Sakura Game Framework : SaFileHandle.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_FILE_HANDLE_H
#define _SA_FILE_HANDLE_H

#include "SaCore.h"
#include "SaCallback.h"
#include <SakuraThread/SaMutex.h>
#include <SakuraThread/SaConditionVariable.h>
#include <cstdio>

namespace Sakura
{
    class SaFileJob;

    class SaFileHandle
    {
    public:
        enum EFlags
        {
            FLAG_CREATE = 1 << 0,
            FLAG_READ = 1 << 1,
            FLAG_WRITE = 1 << 2
        };

        enum EResult
        {
            RESULT_INVALID = -1,
            RESULT_SUCCEEDED,
            RESULT_FAILED,
            RESULT_PROCESSING
        };

        SaFileHandle(const char* pFileName);

        EResult     Open(uint32_t openFlags, bool blockUntilDone, SaCallback<EResult, const SaFileHandle*> callback);
        EResult     Read(uint8_t* pDestination, uint32_t numBytes, bool blockUntilDone, SaCallback<EResult, const SaFileHandle*> callback);
        EResult     Write(const uint8_t* pSource, uint32_t numBytes, bool blockUntilDone, SaCallback<EResult, const SaFileHandle*> callback);
        EResult     Seek(uint32_t position, bool blockUntilDone, SaCallback<EResult, const SaFileHandle*> callback);
        EResult     Close(bool blockUntilDone, SaCallback<EResult, const SaFileHandle*> callback);

        uint32_t    GetSize() const;

    private:
        SaFileJob   CreateJob(SaCallback<const SaFileJob*> jobFunc, SaCallback<EResult, const SaFileHandle*> callback);
        EResult     AddJob(const SaFileJob& rJob, bool block);
        EResult     WaitForJob();
        void        JobDone(const SaFileJob* pJob, EResult result);

        void        FileThread_Open(const SaFileJob* pJob);
        void        FileThread_Read(const SaFileJob* pJob);
        void        FileThread_Write(const SaFileJob* pJob);
        void        FileThread_Seek(const SaFileJob* pJob);
        void        FileThread_Close(const SaFileJob* pJob);

        const char*     m_pFileName;
        uint32_t        m_openFlags;
        FILE*           m_pHandle;
        uint32_t        m_fileSize;
        uint32_t        m_jobCount;

        uint32_t                            m_blockJobIdx;
        EResult                             m_blockJobResult;
        SakuraThread::SaMutex               m_blockMutex;
        SakuraThread::SaConditionVariable   m_blockCondition;
    };
}

#endif  //_SA_FILE_HANDLE_H
