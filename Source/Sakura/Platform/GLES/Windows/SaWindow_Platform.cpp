/***************************************************
Sakura Game Framework : SaWindow_Platform.cpp
Author: Darrell Blake

Windows platform implementation for SaWindow.
***************************************************/

#include "SaWindow_Platform.h"
#include "../../../SaWindow.h"
#include <cstring>
#include "../../../SaDebug.h"
#include "../SaGraphicsAPI.h"

using namespace Sakura;

SaWindow_Platform::SaWindow_Platform(SaWindow* pParent) :
    m_pParent(pParent)
{
}

LRESULT WINAPI WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
   LRESULT  lRet = 1; 

   switch (uMsg) 
   { 
      case WM_CREATE:
         break;

      case WM_PAINT:
         {
             SaWindow_Platform* pPlatform = (SaWindow_Platform*)(LONG_PTR)GetWindowLongPtr(hWnd, GWL_USERDATA);
             ValidateRect(pPlatform->GetHandle(), NULL);
         }
         break;

      case WM_DESTROY:
         PostQuitMessage(0);             
         break; 
      
//     case WM_CHAR:
//         {
//            POINT      point;
//            ESContext *esContext = (ESContext*)(LONG_PTR) GetWindowLongPtr ( hWnd, GWL_USERDATA );
//            
//            GetCursorPos( &point );
//
//            if ( esContext && esContext->keyFunc )
//              esContext->keyFunc ( esContext, (unsigned char) wParam, 
//                                   (int) point.x, (int) point.y );
//}
//         break;
         
      default: 
         lRet = DefWindowProc (hWnd, uMsg, wParam, lParam); 
         break; 
   } 

   return lRet; 
}


bool SaWindow_Platform::Initialise()
{
    WNDCLASS wndclass = {0};
    DWORD    wStyle   = 0;
    RECT     windowRect;
    HINSTANCE hInstance = GetModuleHandle(NULL);

    wndclass.style         = CS_OWNDC;
    wndclass.lpfnWndProc   = (WNDPROC)WindowProc;
    wndclass.hInstance     = hInstance;
    wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndclass.lpszClassName = "SaWindow_Platform";

    if (!RegisterClass(&wndclass))
        return false;

    wStyle = WS_VISIBLE | WS_POPUP | WS_BORDER | WS_SYSMENU | WS_CAPTION;

    windowRect.left = 0;
    windowRect.top = 0;
    windowRect.right = m_pParent->m_width;
    windowRect.bottom = m_pParent->m_height;

    m_windowHandle = CreateWindow("SaWindow_Platform",
                                  m_pParent->m_title,
                                  wStyle,
                                  0,
                                  0,
                                  windowRect.right - windowRect.left,
                                  windowRect.bottom - windowRect.top,
                                  NULL,
                                  NULL,
                                  hInstance,
                                  NULL);

    SetWindowLongPtr(m_windowHandle, GWL_USERDATA, (LONG)(LONG_PTR)this);

    if (m_windowHandle == NULL)
        return false;

    ShowWindow(m_windowHandle, TRUE);

    return true;
}

bool SaWindow_Platform::InitialiseRender()
{
    EGLint const attribList[] = {
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_DEPTH_SIZE, 24,
        EGL_SURFACE_TYPE, 
        EGL_WINDOW_BIT,
        EGL_RENDERABLE_TYPE,
        EGL_OPENGL_ES2_BIT,
        EGL_NONE
    };

    /*EGLint const attribList[] = {
        EGL_SURFACE_TYPE,
        EGL_WINDOW_BIT,
        EGL_RENDERABLE_TYPE,
        EGL_OPENGL_ES2_BIT,
        EGL_NONE
    };*/

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
    if (CheckError("Creating window surface"))
        return false;

    eglBindAPI(EGL_OPENGL_ES_API);
    if (CheckError("Binding API"))
        return false;

    context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs);
    if (CheckError("Creating context"))
        return false;

    eglMakeCurrent(display, surface, surface, context);
    if (CheckError("Making current"))
        return false;

    m_eglDisplay = display;
    m_eglSurface = surface;
    m_eglContext = context;

    return true;
}

void SaWindow_Platform::Release()
{
}

void SaWindow_Platform::Update(uint32_t uDt)
{
    MSG msg = { 0 };
    int gotMsg = (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0);

    if (gotMsg)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void SaWindow_Platform::PreRender()
{
    glViewport(0, 0, m_pParent->m_width, m_pParent->m_height);
    glClearColor(m_pParent->m_clearColour.GetR(), 
                 m_pParent->m_clearColour.GetG(), 
                 m_pParent->m_clearColour.GetB(), 
                 m_pParent->m_clearColour.GetA());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void SaWindow_Platform::PostRender()
{
    eglSwapBuffers(m_eglDisplay, m_eglSurface);
}

bool SaWindow_Platform::CheckError(const char* doing) const
{
    EGLint error = eglGetError();

    if (error != EGL_SUCCESS)
    {
        SA_FAIL("OpenGL error: %s.", doing);
        return true;
    }

    return false;
}
