/*************************************************************
Sakura Game Framework : SaAsyncJobQueue.h
Author: Darrell Blake

Class T must implement a Process() method.
*************************************************************/

#ifndef _SA_ASYNC_JOB_QUEUE_H
#define _SA_ASYNC_JOB_QUEUE_H

#include <Sakura/SaCore.h>
#include "SaMutex.h"
#include "SaConditionVariable.h"
#include <Sakura/SaQueue.h>
#include <vector>

namespace SakuraThread
{
    template <class T>
    class SaAsyncJobQueue
    {
    public:
        SaAsyncJobQueue();
        SaAsyncJobQueue(uint32_t initalCapacity);
        ~SaAsyncJobQueue();

        void        AddJob(const T& rJob);
        void        ProcessJobs(bool blockAndWait);

        void        Kill();

        uint32_t    Size() const;

    private:
        bool                    m_dying;
        mutable SaMutex         m_jobsMutex;
        SaConditionVariable     m_jobsConditionVariable;
        Sakura::SaQueue<T>      m_jobs;
    };
}

#include "SaAsyncJobQueue.inl"

#endif  //_SA_ASYNC_JOB_QUEUE_H
