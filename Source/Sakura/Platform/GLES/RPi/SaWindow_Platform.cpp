/***************************************************
Sakura Game Framework : SaWindow_Platform.cpp
Author: Darrell Blake

Windows platform implementation for RPi.
***************************************************/

#include "SaWindow_Platform.h"
#include <cstring>
#include "../../SaDebug.h"

using namespace Sakura;

SaWindow_Platform::SaWindow_Platform()
{
}

SaWindow_Platform::~SaWindow_Platform()
{
}

bool SaWindow_Platform::Initialise(const char* title, uint32_t width, uint32_t height, SaColour clearColour)
{
    bcm_host_init();

    if (!SaWindow::Initialise(title, width, height, clearColour))
        return false;
    
    static EGL_DISPMANX_WINDOW_T nativeWindow;

    DISPMANX_ELEMENT_HANDLE_T dispman_element;
    DISPMANX_DISPLAY_HANDLE_T dispman_display;
    DISPMANX_UPDATE_HANDLE_T dispman_update;
    VC_RECT_T dst_rect;
    VC_RECT_T src_rect;

    //int success = graphics_get_display_size(0 /*LCD*/, &windowWidth, &windowHeight);
    //if (success < 0)
    //return false;

    dst_rect.x = 0;
    dst_rect.y = 0;
    dst_rect.width = width;
    dst_rect.height = height;

    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.width = width << 16;
    src_rect.height = height << 16;

    dispman_display = vc_dispmanx_display_open(0 /*LCD*/);
    dispman_update = vc_dispmanx_update_start(0);

    dispman_element = vc_dispmanx_element_add(dispman_update,
                                              dispman_display,
                                              0, /*Layer*/
                                              &dst_rect,
                                              0, /*Src*/
                                              &src_rect,
                                              DISPMANX_PROTECTION_NONE,
                                              0, /*Alpha*/
                                              0, /*Clamp*/
                                              DISPMANX_NO_ROTATE /*Transform*/);

    nativeWindow.element = dispman_element;
    nativeWindow.width = width;
    nativeWindow.height = height;
    
    vc_dispmanx_update_submit_sync(dispman_update);

    m_windowHandle = &nativeWindow;
    



    EGLint const attribList[] = {
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_DEPTH_SIZE, 24,
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_NONE
    };

    EGLint numConfigs;
    EGLint majorVersion;
    EGLint minorVersion;
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    EGLConfig config;
    EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };

    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    if (display == EGL_NO_DISPLAY)
        return false;

    if (!eglInitialize(display, &majorVersion, &minorVersion))
        return false;

    if (!eglGetConfigs(display, NULL, 0, &numConfigs))
        return false;

    if (!eglChooseConfig(display, attribList, &config, 1, &numConfigs))
        return false;

    surface = eglCreateWindowSurface(display, config, m_windowHandle, NULL);
    if (surface == EGL_NO_SURFACE)
        return false;

    context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs);
    if (context == EGL_NO_CONTEXT)
        return false;

    if (!eglMakeCurrent(display, surface, surface, context))
        return false;

    m_eglDisplay = display;
    m_eglSurface = surface;
    m_eglContext = context;

    return true;
}

void SaWindow_Platform::Release()
{
    SaWindow::Release();
}

void SaWindow_Platform::Update(uint32_t uDt)
{
    SaWindow::Update(uDt);
}

void SaWindow_Platform::PreRender()
{
    SaWindow::PreRender();
}

void SaWindow_Platform::PostRender()
{
    SaWindow::PostRender();
    eglSwapBuffers(m_eglDisplay, m_eglSurface);
}
