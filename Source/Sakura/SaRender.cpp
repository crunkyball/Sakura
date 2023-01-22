/*************************************************************
Sakura Game Framework : SaRender.cpp
Author: Darrell Blake
*************************************************************/

#include "SaRender.h"
#include "SaDebug.h"

using namespace Sakura;
using namespace SakuraThread;

bool SaRender::ms_renderThreadExit = false;
SaThread SaRender::ms_renderThread;
SaAsyncJobQueue<SaRenderJob> SaRender::ms_renderJobs;
uint32_t SaRender::ms_currentWorkingFrame = 0;
uint32_t SaRender::ms_currentRenderFrame = 2;
uint32_t SaRender::ms_lastFullFrame = 2;
SaMutex SaRender::ms_jobsMutex;
SaQueue<SaRenderJob> SaRender::ms_renderFrameJobs[NUM_FRAMES];
SaConditionVariable SaRender::ms_renderWaitConditionVariable;

void SaRender::Initialise()
{
    ms_renderThreadExit = false;

    ms_renderThread.Initialise("Render Thread", RenderThread_Main, NULL, SakuraThread::PRIORITY_HIGHEST);
    ms_renderThread.Run();
}

void SaRender::Release()
{
    ms_renderJobs.Kill();

    ms_jobsMutex.Lock();
    ms_renderThreadExit = true;
    ms_renderWaitConditionVariable.Signal();
    ms_jobsMutex.Unlock();

    ms_renderThread.Join();
}

void SaRender::AddRenderJob(const SaRenderJob& rJob)
{
    ms_renderJobs.AddJob(rJob);

    ms_jobsMutex.Lock();
    ms_renderWaitConditionVariable.Signal();
    ms_jobsMutex.Unlock();
}

void SaRender::AddRenderFrameJob(const SaRenderJob& rJob)
{
    ms_jobsMutex.Lock();
    ms_renderFrameJobs[ms_currentWorkingFrame].Push(rJob);
    ms_jobsMutex.Unlock();
}

void SaRender::NextFrame()
{
    ms_jobsMutex.Lock();

    ms_lastFullFrame = ms_currentWorkingFrame;
    ms_renderWaitConditionVariable.Signal();

    do 
    {
        ms_currentWorkingFrame = (ms_currentWorkingFrame + 1) % NUM_FRAMES;
    } while (ms_currentWorkingFrame == ms_currentRenderFrame || ms_currentWorkingFrame == ms_lastFullFrame);

    //If this frame isn't empty then it means that the render thread hasn't gotten time to 
    //rendering it, so just replace it.
    if (ms_renderFrameJobs[ms_currentWorkingFrame].Size() > 0)
        ms_renderFrameJobs[ms_currentWorkingFrame].Clear();

    ms_jobsMutex.Unlock();
}

void SaRender::RenderThread_Main()
{
    while (!ms_renderThreadExit)
    {
        ms_renderJobs.ProcessJobs(false);

        ms_jobsMutex.Lock();
        uint32_t renderFrame = ms_currentRenderFrame;
        ms_jobsMutex.Unlock();

        while (ms_renderFrameJobs[renderFrame].Size() > 0)
        {
            SaRenderJob job = ms_renderFrameJobs[renderFrame].Front();
            ms_renderFrameJobs[renderFrame].Pop();
            job.Process();
        }

        ms_jobsMutex.Lock();
        while (ms_currentRenderFrame == ms_lastFullFrame && ms_renderJobs.Size() == 0 && !ms_renderThreadExit)
        {
            //Wait for there to be more jobs.
            ms_renderWaitConditionVariable.Wait(ms_jobsMutex);
        }
        ms_currentRenderFrame = ms_lastFullFrame;

        ms_jobsMutex.Unlock();
    }
}

void SaRender::SetDepthTest(bool enable)
{
    SaRenderJob job(BIND_FUNC(&SaRender::RenderThreadJob_SetDepthTest));
    job.SetEnable(enable);
    AddRenderFrameJob(job);
}

void SaRender::SetAlphaBlending(bool enable)
{
    SaRenderJob job(BIND_FUNC(&SaRender::RenderThreadJob_SetAlphaBlending));
    job.SetEnable(enable);
    AddRenderFrameJob(job);
}

void SaRender::SetBackFaceCulling(bool enable)
{
    SaRenderJob job(BIND_FUNC(&SaRender::RenderThreadJob_SetBackFaceCulling));
    job.SetEnable(enable);
    AddRenderFrameJob(job);
}

void SaRender::RenderThread_ClearCurrentFrameJobs()
{
    ms_renderFrameJobs[ms_currentRenderFrame].Clear();
}
