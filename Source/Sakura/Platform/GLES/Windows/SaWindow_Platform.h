/***************************************************
Sakura Game Framework : SaWindow_Platform.h
Author: Darrell Blake

Windows platform implementation for SaWindow.
***************************************************/

#ifndef _SA_WINDOW_PLATFORM_H
#define _SA_WINDOW_PLATFORM_H

#include "../../../SaCore.h"
#include <EGL/egl.h>

namespace Sakura
{
    class SaWindow;

    class SaWindow_Platform
    {
    public:
        SaWindow_Platform(SaWindow* pParent);

        bool Initialise();
        bool InitialiseRender();
        void Release();

        void Update(uint32_t uDt);

        void PreRender();
        void PostRender();

        EGLNativeWindowType GetHandle() { return m_windowHandle; }

    private:
        bool CheckError(const char* doing) const;

        SaWindow*           m_pParent;
        EGLNativeWindowType m_windowHandle;
        EGLDisplay          m_eglDisplay;
        EGLSurface          m_eglSurface;
        EGLContext          m_eglContext;
    };
}

#endif  //_SA_WINDOW_PLATFORM_H
