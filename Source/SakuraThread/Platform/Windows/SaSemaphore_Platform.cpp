/*************************************************************
Sakura Game Framework : SaSemaphore_Platform.cpp
Author: Darrell Blake

Windows platform implementation for SaSemaphore.
*************************************************************/

#include "SaSemaphore_Platform.h"
#include "../../SaSemaphore.h"
#include <Sakura/SaDebug.h>

using namespace SakuraThread;

SaSemaphore_Platform::SaSemaphore_Platform(SaSemaphore* pParent) :
    m_pParent(pParent),
    m_handle(NULL)
{
}

SaSemaphore_Platform::~SaSemaphore_Platform()
{
}

bool SaSemaphore_Platform::Initialise()
{
    SA_ASSERT(!m_handle, "Already initialised.");

    m_handle = CreateSemaphore(NULL, m_pParent->m_initialCount, m_pParent->m_maxCount, NULL);

    if (m_handle == NULL)
    {
        SA_FAIL("Error creating semaphore (code %d).\n", GetLastError());
        return false;
    }

    return true;
}

void SaSemaphore_Platform::Release()
{
    SA_ASSERT(m_handle, "Not initialised.");

    if (m_handle)
    {
        CloseHandle(m_handle);
        m_handle = NULL;
    }
}

bool SaSemaphore_Platform::Wait(uint32_t timeout)
{
    SA_ASSERT(m_handle, "Not initialised.");

    if (timeout == 0)
        timeout = INFINITE;

    uint32_t retVal = WaitForSingleObject(m_handle, timeout);

    SA_WARNING(retVal == WAIT_OBJECT_0, "Warning: Semaphore wait ended unsuccessfully.");

    if (retVal == WAIT_FAILED)
    {
        SA_FAIL("Error waiting for semaphore (code %d).\n", GetLastError());
    }

    return retVal == WAIT_OBJECT_0;
}

bool SaSemaphore_Platform::Signal(uint32_t num)
{
    SA_ASSERT(m_handle, "Not initialised.");

    BOOL success = ReleaseSemaphore(m_handle, num, NULL);

    SA_ASSERT(success, "Failed to signal semaphore.");

    return success != 0;
}
