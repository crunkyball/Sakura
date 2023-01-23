/*************************************************************
Sakura Game Framework : SaWindow.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_WINDOW_H
#define _SA_WINDOW_H

#include "SaCore.h"
#include "SaColour.h"
#include "SaViewport.h"
#include PLATFORM_INCLUDE( SA_WINDOW_API_DIR/SaWindow_Platform.h )

namespace Sakura
{
    class SaScene;
    class SaRenderJob;
    class SaKeyboardInputHandler;

    class SaWindow
    {
        friend class SaWindow_Platform;

    public:
        struct ViewportConfig
        {
            uint32_t xPosition;
            uint32_t yPosition;
            uint32_t width;
            uint32_t height;
        };

        SaWindow();

        static bool InitialiseSystem() { return SaWindow_Platform::InitialiseSystem(); }
        static void UpdateSystem() { SaWindow_Platform::UpdateSystem(); }
        static void TerminateSystem() { SaWindow_Platform::TerminateSystem(); }

        void Initialise(const char* title, uint32_t width, uint32_t height, SaColour clearColour = SaColour::SAKURA);
        void Release();

        void Update(uint32_t dt);

        void PreRender();
        void PostRender();

        bool IsInitialised() const { return m_state == STATE_INITIALISED; }
        bool IsError() const { return m_state == STATE_ERROR; }

        void SetViewports(uint32_t numViewports, const ViewportConfig* configs);

        uint32_t GetNumViewports() const { return m_numViewPorts; }
        SaViewport& GetViewport(uint32_t viewportIdx = 0) { return m_viewports[viewportIdx]; }

        void SetKeyboardInputHandler(const SaKeyboardInputHandler* pHandler);

    private:
        void RenderThread_Initialise(const SaRenderJob* pJob);
        void RenderThread_PreRender(const SaRenderJob* pJob);
        void RenderThread_PostRender(const SaRenderJob* pJob);

        enum EState
        {
            STATE_UNITIALISED,
            STATE_INITIALISED,
            STATE_ERROR
        };

        SaWindow_Platform m_platformWindow;

        static const char* DEFAULT_TITLE;

        static const uint32_t MAX_VIEWPORTS = 4;
        uint32_t m_numViewPorts;
        SaViewport m_viewports[MAX_VIEWPORTS];

        EState m_state;

        static const uint32_t TITLE_LENGTH = 128;
        char m_title[TITLE_LENGTH];

        uint32_t m_width;
        uint32_t m_height;
        SaColour m_clearColour;

        const SaKeyboardInputHandler* m_pKeyboardInputHandler;
    };
}

#endif  //_SA_WINDOW_H
