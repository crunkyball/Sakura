/*************************************************************
Sakura Game Framework : SaFile.cpp
Author: Darrell Blake
*************************************************************/

#include "SaFile.h"

using namespace Sakura;
using namespace SakuraThread;

bool SaFile::ms_fileThreadExit = false;
SaThread SaFile::ms_fileThread;
SaAsyncJobQueue<SaFileJob> SaFile::ms_fileJobQueue;

void SaFile::Initialise()
{
    ms_fileThreadExit = false;

    ms_fileThread.Initialise("File Thread", FileThread_Main);
    ms_fileThread.Run();
}

void SaFile::Release()
{
    ms_fileThreadExit = true;
    ms_fileJobQueue.Kill();
    ms_fileThread.Join();
}

void SaFile::OpenFile(SaFileHandle*& rpHandleOut, const char* pFilename, uint32_t openFlags, bool blockUntilDone, SaCallback<SaFileHandle::EResult, const SaFileHandle*> callback)
{
    rpHandleOut = new SaFileHandle(pFilename);

    if (rpHandleOut)
    {
        rpHandleOut->Open(openFlags, blockUntilDone, callback);
    }
}

void SaFile::AddJob(const SaFileJob& rJob)
{
    ms_fileJobQueue.AddJob(rJob);
}

void SaFile::FileThread_Main()
{
    while (!ms_fileThreadExit)
    {
        ms_fileJobQueue.ProcessJobs(true);
    }
}
