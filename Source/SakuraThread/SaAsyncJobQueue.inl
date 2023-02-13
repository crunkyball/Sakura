/*************************************************************
Sakura Game Framework : SaAsyncJobQueue.inl
Author: Darrell Blake
*************************************************************/

#ifndef _SA_ASYNC_JOB_QUEUE_H
#error This should be included from SaAsyncJobQueue.h
#endif

#include <Sakura/SaDebug.h>

namespace SakuraThread
{

template <class T>
SaAsyncJobQueue<T>::SaAsyncJobQueue() :
    m_dying(false)
{
}

template <class T>
SaAsyncJobQueue<T>::SaAsyncJobQueue(uint32_t initialCapacity) :
    m_jobs(initialCapacity),
    m_dying(false)
{
}

template <class T>
SaAsyncJobQueue<T>::~SaAsyncJobQueue()
{
    SA_ASSERT(m_dying, "Wasn't killed.");
}

template <class T>
void SaAsyncJobQueue<T>::AddJob(const T& rJob)
{
    m_jobsMutex.Lock();

    SA_WARNING(!m_dying, "Warning: Job won't be added as queue is dead!");

    if (!m_dying)
    {
        m_jobs.Push(rJob);
        m_jobsConditionVariable.Signal();
    }

    m_jobsMutex.Unlock();
}

template <class T>
void SaAsyncJobQueue<T>::ProcessJobs(bool blockAndWait)
{
    m_jobsMutex.Lock();

    while (m_jobs.Size() == 0 && blockAndWait && !m_dying)
    {
        m_jobsConditionVariable.Wait(m_jobsMutex);
    }

    while (m_jobs.Size() > 0)
    {
        T job = m_jobs.Front();
        m_jobs.Pop();

        m_jobsMutex.Unlock();
        job.Process();
        m_jobsMutex.Lock();
    }

    m_jobsMutex.Unlock();
}

template <class T>
void SaAsyncJobQueue<T>::Kill()
{
    m_jobsMutex.Lock();
    m_dying = true;
    m_jobsConditionVariable.Signal();
    m_jobsMutex.Unlock();
}

template <class T>
uint32_t SaAsyncJobQueue<T>::Size() const 
{
    uint32_t numJobs = 0;

    m_jobsMutex.Lock();
    numJobs = m_jobs.Size();
    m_jobsMutex.Unlock();

    return numJobs;
}

}
