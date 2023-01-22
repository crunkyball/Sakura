/***************************************************
Sakura Game Framework : SaWindow_Platform.h
Author: Darrell Blake

RPi platform implementation for SaWindow.
***************************************************/

#ifndef _SA_WINDOW_PLATFORM_H
#define _SA_WINDOW_PLATFORM_H

#include "../../SaWindow.h"
#include <GLES2/gl2.h>
#include <EGL/egl.h>

namespace Sakura
{
    class SaWindow_Platform : public SaWindow
    {
    public:
        SaWindow_Platform();
        virtual ~SaWindow_Platform();

        virtual bool Initialise(const char* title, uint32_t width, uint32_t height, SaColour clearColour = SaColour::SAKURA);
        virtual void Release();

        virtual void Update(uint32_t uDt);

        virtual void PreRender();
        virtual void PostRender();

    //private:
        EGLNativeWindowType m_windowHandle;
        EGLDisplay m_eglDisplay;
        EGLSurface m_eglSurface;
        EGLContext m_eglContext;
    };
}

#endif  //_SA_WINDOW_PLATFORM_H
