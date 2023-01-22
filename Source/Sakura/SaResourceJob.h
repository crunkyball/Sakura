/*************************************************************
Sakura Game Framework : SaResourceJob.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_RESOURCE_JOB_H
#define _SA_RESOURCE_JOB_H

#include "SaCore.h"
#include "SaResource.h"

namespace Sakura
{
    class SaResourceJob
    {
    public:
        typedef void (*ProcessJobFunc)(const SaResourceJob* pJob);

        SaResourceJob();
        SaResourceJob(uint32_t resourceHash, ProcessJobFunc processJobFunc);

        uint32_t GetResourceHash() const { return m_resourceHash; }

        void SetFileName(const char* pFileName) { m_pFileName = pFileName; }
        const char* GetFileName() const { return m_pFileName; }

        void Process();

    private:
        uint32_t            m_resourceHash;
        ProcessJobFunc      m_jobFunc;

        const char*         m_pFileName;
    };
}

#endif  //_SA_RESOURCE_JOB_H
