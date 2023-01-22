/*************************************************************
Sakura Game Framework : SaThread.cpp
Author: Darrell Blake
*************************************************************/

#include "SaThread.h"

using namespace SakuraThread;

SaThread::SaThread() :
    m_platformThread(this),
    m_threadName(NULL),
    m_threadPriority(PRIORITY_NORMAL),
    m_pFunction(NULL),
    m_pUserData(NULL)
{
}

SaThread::~SaThread()
{
}

bool SaThread::Initialise(const char* threadName, void* pFunction, void* pUserData, EThreadPriority threadPriority)
{
    m_threadName = threadName;
    m_threadPriority = threadPriority;
    m_pFunction = pFunction;
    m_pUserData = pUserData;

    return m_platformThread.Initialise();
}

void SaThread::Release()
{
    m_platformThread.Release();
}

void SaThread::Run()
{
    m_platformThread.Run();
}

bool SaThread::Wait(uint32_t timeout)
{
    return m_platformThread.Wait(timeout);
}

void SaThread::Join()
{
    m_platformThread.Join();
}
