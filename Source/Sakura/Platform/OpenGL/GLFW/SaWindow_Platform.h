/*************************************************************
Sakura Game Framework : SaWindow_Platform.h
Author: Darrell Blake

OpenGL/GLFW platform implementation for SaWindow.
*************************************************************/

#ifndef _SA_WINDOW_PLATFORM_H
#define _SA_WINDOW_PLATFORM_H

#include "../../../SaCore.h"
#include "../../../SaKeyboard.h"

class GLFWwindow;

namespace Sakura
{
    class SaWindow;

    class SaWindow_Platform
    {
    public:
        SaWindow_Platform(SaWindow* pParent);

        static bool InitialiseSystem();
        static void UpdateSystem();
        static void TerminateSystem();

        bool    Initialise();
        bool    InitialiseRender();
        void    Release();

        void    Update(uint32_t dt);

        void    PreRender();
        void    PostRender();

    private:
        static void KeyInputCallback(GLFWwindow* pWindow, int key, int scanCode, int action, int mods);
        void OnKeyInput(int key, int scanCode, int action, int mods);

        SaKeyCode GetKeyCode(int glfwKeyCode);

        static const uint32_t       MAX_WINDOWS = 2;
        static SaWindow_Platform*   ms_currentWindows[MAX_WINDOWS];

        SaWindow*       m_pParent;
        GLFWwindow*     m_pWindow;
    };
}

#endif  //_SA_WINDOW_PLATFORM_H
