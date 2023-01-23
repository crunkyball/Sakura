/*************************************************************
Sakura Game Framework : SaRender.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_RENDER_H
#define _SA_RENDER_H

#include "SaCore.h"
#include "SaRenderJob.h"
#include "SaQueue.h"
#include <SakuraThread/SaThread.h>
#include <SakuraThread/SaMutex.h>
#include <SakuraThread/SaConditionVariable.h>
#include <SakuraThread/SaAsyncJobQueue.h>

namespace Sakura
{
    class SaRender
    {
    public:
        static void     Initialise();
        static void     Release();

        //Frame jobs can be discarded as old if the render thread hasn't gotten around to 
        //rendering that particular frame yet. Important render jobs, such as loading assets 
        //etc, should use AddRenderJob to guarantee they happen. However, it is important to 
        //remember that order may not be preserved between these two systems. Any non-frame 
        //jobs will always be processed before any frame jobs. Also, non-frame jobs are 
        //processed immediately, whereas frame jobs are queued up until the next frame.
        static void     AddRenderJob(const SaRenderJob& rJob);
        static void     AddRenderFrameJob(const SaRenderJob& rJob);

        static void     NextFrame();

        static void     SetDepthTest(bool enable);
        static void     SetAlphaBlending(bool enable);
        static void     SetBackFaceCulling(bool enable);

        //These MUST be called from the render thread!
        static void     RenderThread_Initialise();
        static void     RenderThread_SetDepthTest(bool enable);
        static void     RenderThread_SetAlphaBlending(bool enable);
        static void     RenderThread_SetBackFaceCulling(bool enable);
        
        //This isn't ideal but it will do until I can think of a better solution. Basically, there 
        //are occasions where we may have jobs in the frame queues that depend on assets that could 
        //be unloaded via jobs in the non-frame queue. Even if these jobs are added in the correct 
        //order, because frame jobs are delayed, the assets will be unloaded by the time the frame 
        //jobs come around. So, for situations like this, where we can't guarantee the reliability 
        //of the queues, we allow the render queue to be cleared.
        static void     RenderThread_ClearCurrentFrameJobs();

    private:
        static void     RenderThread_Main();

        static void     RenderThreadJob_Initialise(const SaRenderJob* pJob) { RenderThread_Initialise(); }
        static void     RenderThreadJob_SetDepthTest(const SaRenderJob* pJob) { RenderThread_SetDepthTest(pJob->GetEnable()); }
        static void     RenderThreadJob_SetAlphaBlending(const SaRenderJob* pJob) { RenderThread_SetAlphaBlending(pJob->GetEnable()); }
        static void     RenderThreadJob_SetBackFaceCulling(const SaRenderJob* pJob) { RenderThread_SetBackFaceCulling(pJob->GetEnable()); }

        static bool                                         ms_renderThreadExit;
        static SakuraThread::SaThread                       ms_renderThread;

        static SakuraThread::SaAsyncJobQueue<SaRenderJob>   ms_renderJobs;

        static const uint32_t                               NUM_FRAMES = 3;
        static uint32_t                                     ms_lastFullFrame;
        static uint32_t                                     ms_currentWorkingFrame;
        static uint32_t                                     ms_currentRenderFrame;

        static SakuraThread::SaMutex                        ms_jobsMutex;
        static SaQueue<SaRenderJob>                         ms_renderFrameJobs[NUM_FRAMES];
        static SakuraThread::SaConditionVariable            ms_renderWaitConditionVariable;
    };
}

#endif  //_SA_RENDER_H
