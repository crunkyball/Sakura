/*************************************************************
Sakura Game Framework : SaFileLoader.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_FILE_LOADER_H
#define _SA_FILE_LOADER_H

#include "SaCore.h"
#include "SaFileHandle.h"
#include "SaCallback.h"
#include <SakuraThread/SaConditionVariable.h>

namespace Sakura
{
    class SaFileLoader
    {
    public:
        SaFileLoader();
        ~SaFileLoader();

        enum EResult
        {
            RESULT_INVALID,
            RESULT_LOADING,
            RESULT_SUCCEEDED,
            RESULT_FAILED
        };

        void Load(const char* pFileName, SaCallback<EResult> callback, bool addNTC = false, bool blockUntilDone = false);
        void Release(SaCallback<EResult> callback, bool blockUntilDone = false);

        bool InUse() const { return m_result != RESULT_INVALID; }
        bool IsDone() const { return m_result == RESULT_SUCCEEDED || m_result == RESULT_FAILED; }
        bool Succeeded() const { return m_result == RESULT_SUCCEEDED; }

        const uint8_t* GetDataPtr() const { return m_pFileData; }
        const uint32_t GetSize() const { return m_fileSize; }

    private:
        void Done(SaFileHandle::EResult result);

        void OnFileOpen(SaFileHandle::EResult result, const SaFileHandle* pFileHandle);
        void OnFileRead(SaFileHandle::EResult result, const SaFileHandle* pFileHandle);
        void OnFileClose(SaFileHandle::EResult result, const SaFileHandle* pFileHandle);

        EResult                             m_result;
        SaFileHandle*                       m_pFileHandle;
        uint8_t*                            m_pFileData;
        uint32_t                            m_fileSize;
        bool                                m_addNTC;
        SaCallback<EResult>                 m_callback;

        SakuraThread::SaMutex               m_doneMutex;
        SakuraThread::SaConditionVariable   m_doneCondition;
    };
}

#endif  //_SA_FILE_LOADER_H
