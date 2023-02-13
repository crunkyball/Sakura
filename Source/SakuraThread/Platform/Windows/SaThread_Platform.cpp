/*************************************************************
Sakura Game Framework : SaThread_Platform.cpp
Author: Darrell Blake

Windows platform implementation for SaThread.
*************************************************************/

#include "SaThread_Platform.h"
#include "../../SaThread.h"
#include <Sakura/SaDebug.h>

using namespace SakuraThread;

SaThread_Platform::SaThread_Platform(SaThread* pParent) : 
    m_pParent(pParent),
    m_handle(NULL)
{
}

SaThread_Platform::~SaThread_Platform()
{
}

struct ThreadnameInfo
{
    DWORD type;
    LPCSTR name;
    DWORD threadID;
    DWORD flags;
};

static void SetThreadName( DWORD threadID, LPCSTR threadName)
{
    ThreadnameInfo info;
    {
        info.type = 0x1000;
        info.name = threadName;
        info.threadID = threadID;
        info.flags = 0;
    }
    __try
    {
        RaiseException( 0x406D1388, 0, sizeof(info)/sizeof(DWORD), (DWORD_PTR*)&info );
    }
    __except (EXCEPTION_CONTINUE_EXECUTION)
    {
    }
}

bool SaThread_Platform::Initialise()
{
    SA_ASSERT(!m_handle, "Already initialised.");

    int32_t threadId = 0;
    m_handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)m_pParent->m_pFunction, m_pParent->m_pUserData, CREATE_SUSPENDED, (LPDWORD)&threadId);

    if (!m_handle)
    {
        SA_FAIL("Error creating thread (code %d).\n", GetLastError());
        return false;
    }

    SetThreadName(threadId, m_pParent->m_threadName);

    int priority = THREAD_PRIORITY_NORMAL;

    switch(m_pParent->m_threadPriority)
    {
        case SakuraThread::PRIORITY_HIGHEST: priority = THREAD_PRIORITY_HIGHEST; break;
        case SakuraThread::PRIORITY_HIGH: priority = THREAD_PRIORITY_ABOVE_NORMAL; break;
        case SakuraThread::PRIORITY_NORMAL: priority = THREAD_PRIORITY_NORMAL; break;
        case SakuraThread::PRIORITY_LOW: priority = THREAD_PRIORITY_LOWEST; break;
    }

    SetThreadPriority(m_handle, priority);

    return true;
}

void SaThread_Platform::Release()
{
    CloseHandle(m_handle);
    m_handle = NULL;
}

void SaThread_Platform::Run()
{
    SA_ASSERT(m_handle, "Not initialised.");

    if (ResumeThread(m_handle) == -1)
    {
        SA_FAIL("Error starting thread (code %d).\n", GetLastError());
    }
}

bool SaThread_Platform::Wait(uint32_t timeout)
{
    SA_ASSERT(m_handle, "Not initialised.");

    if (timeout == 0)
        timeout = INFINITE;

    uint32_t retVal = WaitForSingleObject(m_handle, timeout);

    SA_WARNING(retVal == WAIT_OBJECT_0, "Warning: Thread wait ended unsuccessfully.");

    if (retVal == WAIT_FAILED)
    {
        SA_FAIL("Error waiting for thread (code %d).\n", GetLastError());
    }

    return retVal == WAIT_OBJECT_0;
}

void SaThread_Platform::Join()
{
    WaitForSingleObject(m_handle, INFINITE);
}

void SaThread_Platform::Sleep(uint32_t milliseconds)
{
    ::Sleep(milliseconds);
}
