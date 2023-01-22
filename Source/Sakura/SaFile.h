/*************************************************************
Sakura Game Framework : SaFile.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_FILE_H
#define _SA_FILE_H

#include "SaCore.h"
#include "SaCallback.h"
#include "SaFileHandle.h"
#include "SaFileJob.h"
#include <SakuraThread/SaThread.h>
#include <SakuraThread/SaAsyncJobQueue.h>

namespace Sakura
{
    class SaFile
    {
        friend class SaFileHandle;

    public:
        static void     Initialise();
        static void     Release();

        //This file will not return an open handle immediately, unless you use the block
        //flag, as all operations are handled asynchronously on the file thread.
        static void     OpenFile(SaFileHandle*& rpHandleOut, const char* pFilename, uint32_t openFlags, bool blockUntilDone, SaCallback<SaFileHandle::EResult, const SaFileHandle*> callback);

    private:
        static void             AddJob(const SaFileJob& rJob);

        static void             FileThread_Main();

        static bool                                     ms_fileThreadExit;
        static SakuraThread::SaThread                   ms_fileThread;
        static SakuraThread::SaAsyncJobQueue<SaFileJob> ms_fileJobQueue;
    };
}

#endif  //_SA_FILE_H
