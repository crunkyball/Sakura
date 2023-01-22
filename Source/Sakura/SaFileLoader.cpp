#include "SaFileLoader.h"
#include "SaFile.h"
#include "SaDebug.h"

using namespace Sakura;
using namespace SakuraThread;

SaFileLoader::SaFileLoader() :
    m_result(RESULT_INVALID),
    m_pFileHandle(NULL),
    m_pFileData(NULL),
    m_fileSize(0),
    m_addNTC(false)
{
}

SaFileLoader::~SaFileLoader()
{
    if (m_pFileData)
    {
        SA_FAIL("Not been released!");
        delete[] m_pFileData;
    }
}

void SaFileLoader::Load(const char* pFileName, SaCallback<EResult> callback, bool addNTC, bool blockUntilDone)
{
    m_result = RESULT_LOADING;
    m_callback = callback;
    m_addNTC = addNTC;
    SaFile::OpenFile(m_pFileHandle, pFileName, SaFileHandle::FLAG_READ, false, BIND_MEMBER_FUNC(&SaFileLoader::OnFileOpen, this));

    if (blockUntilDone)
    {
        m_doneMutex.Lock();
        while (!IsDone())
        {
            m_doneCondition.Wait(m_doneMutex);
        }
        m_doneMutex.Unlock();
    }
}

void SaFileLoader::Release(SaCallback<EResult> callback, bool blockUntilDone)
{
    m_pFileHandle->Close(blockUntilDone, BIND_MEMBER_FUNC(&SaFileLoader::OnFileClose, this));

    delete[] m_pFileData;
    m_pFileData = NULL;
    m_fileSize = 0;
    m_result = RESULT_INVALID;
}

void SaFileLoader::OnFileOpen(SaFileHandle::EResult result, const SaFileHandle* pFileHandle)
{
    SA_ASSERT(m_pFileHandle == pFileHandle, "Incorrect file!");

    if (result == SaFileHandle::RESULT_SUCCEEDED)
    {
        m_fileSize = m_pFileHandle->GetSize() + (m_addNTC ? 1 : 0);
        m_pFileData = new uint8_t[m_fileSize];
        m_pFileHandle->Read(m_pFileData, m_pFileHandle->GetSize(), false, BIND_MEMBER_FUNC(&SaFileLoader::OnFileRead, this));
    }
    else
    {
        SA_FAIL("Failed to open file.");
        Done(result);
    }
}

void SaFileLoader::OnFileRead(SaFileHandle::EResult result, const SaFileHandle* pFileHandle)
{
    SA_ASSERT(m_pFileHandle == pFileHandle, "Incorrect file!");

    if (m_addNTC && result == SaFileHandle::RESULT_SUCCEEDED)
        m_pFileData[m_pFileHandle->GetSize()] = 0;

    SA_ASSERT(result == SaFileHandle::RESULT_SUCCEEDED, "Failed to read file.");

    Done(result);
}

void SaFileLoader::OnFileClose(SaFileHandle::EResult result, const SaFileHandle* pFileHandle)
{
    SA_ASSERT(result == SaFileHandle::RESULT_SUCCEEDED, "Failed to close file.");
}

void SaFileLoader::Done(SaFileHandle::EResult result)
{
    m_doneMutex.Lock();
    m_result = result == SaFileHandle::RESULT_SUCCEEDED ? RESULT_SUCCEEDED : RESULT_FAILED;
    m_doneMutex.Unlock();
    m_doneCondition.Signal();

    m_callback(m_result);
}
