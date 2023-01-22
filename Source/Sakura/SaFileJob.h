/*************************************************************
Sakura Game Framework : SaFileJob.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_FILE_JOB_H
#define _SA_FILE_JOB_H

#include "SaCallback.h"
#include "SaFileHandle.h"

namespace Sakura
{
    class SaFileJob
    {
    public:
        SaFileJob();
        SaFileJob(uint32_t jobIdx, SaCallback<const SaFileJob*> jobFunc, SaCallback<SaFileHandle::EResult, const SaFileHandle*> callback);

        void    Process();

        uint32_t                                                GetJobIndex() const;
        SaCallback<SaFileHandle::EResult, const SaFileHandle*>  GetCallbackFunc() const;

        uint8_t*                            GetDestination() const;
        void                                SetDestination(uint8_t* pDestination);

        const uint8_t*                      GetSource() const;
        void                                SetSource(const uint8_t* pSource);

        uint32_t                            GetNumBytes() const;
        void                                SetNumBytes(uint32_t numBytes);

    private:
        uint32_t                                                m_jobIdx;
        SaFileHandle::EResult                                   m_jobResult;

        SaCallback<const SaFileJob*>                            m_jobFunc;
        SaCallback<SaFileHandle::EResult, const SaFileHandle*>  m_callback;

        uint8_t*                                                m_pDestination;
        const uint8_t*                                          m_pSource;
        uint32_t                                                m_numBytes;
    };
}

#endif  //_SA_FILE_JOB_H
