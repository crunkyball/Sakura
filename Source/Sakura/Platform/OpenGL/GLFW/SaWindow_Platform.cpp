/*************************************************************
Sakura Game Framework : SaWindow_Platform.cpp
Author: Darrell Blake

OpenGL/GLFW platform implementation for SaWindow.
*************************************************************/

#include "SaWindow_Platform.h"
#include "../../../SaWindow.h"
#include "../../../SaDebug.h"
#include "../SaGraphicsAPI.h"
#include <GLFW/glfw3.h>

using namespace Sakura;

SaWindow_Platform* SaWindow_Platform::ms_currentWindows[MAX_WINDOWS] = { NULL, NULL };

SaWindow_Platform::SaWindow_Platform(SaWindow* pParent) : 
    m_pParent(pParent)
{
}

bool SaWindow_Platform::InitialiseSystem()
{
    if (!glfwInit())
    {
        SA_FAIL("Error initialising GLFW.");
        return false;
    }

    return true;
}

void SaWindow_Platform::UpdateSystem()
{
    glfwPollEvents();
}

void SaWindow_Platform::TerminateSystem()
{
    glfwTerminate();
}

bool SaWindow_Platform::Initialise()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    m_pWindow = glfwCreateWindow(m_pParent->m_width, m_pParent->m_height, m_pParent->m_title, NULL, NULL);

    if (!m_pWindow)
    {
        SA_FAIL("Error creating GLFW window.");
        return false;
    }

    bool foundSpace = false;

    for (int windowIdx = 0; windowIdx < MAX_WINDOWS; windowIdx++)
    {
        if (ms_currentWindows[windowIdx] == NULL)
        {
            ms_currentWindows[windowIdx] = this;
            foundSpace = true;
        }
    }

    if (!foundSpace)
    {
        SA_FAIL("No space for window.");
        return false;
    }

    glfwSetKeyCallback(m_pWindow, KeyInputCallback);

    return true;
}

bool SaWindow_Platform::InitialiseRender()
{
    glfwMakeContextCurrent(m_pWindow);

#ifdef SA_PLATFORM_WINDOWS
    uint32_t glewError = glewInit();
    if (glewError != GLEW_OK)
    {
        SA_FAIL("Failed to init glew!");
        return false;
    }
#endif

    return true;
}

void SaWindow_Platform::Release()
{
    bool found = false;

    for (int windowIdx = 0; windowIdx < MAX_WINDOWS; windowIdx++)
    {
        if (!found)
        {
            if (ms_currentWindows[windowIdx] == this)
            {
                found = true;
                ms_currentWindows[windowIdx] = NULL;
            }
        }
        else
        {
            ms_currentWindows[windowIdx-1] = ms_currentWindows[windowIdx];
            ms_currentWindows[windowIdx] = NULL;
        }
    }

    glfwDestroyWindow(m_pWindow);
}

void SaWindow_Platform::Update(uint32_t dt)
{
}

void SaWindow_Platform::PreRender()
{
    glEnable(GL_SCISSOR_TEST);
}

void SaWindow_Platform::PostRender()
{
    glDisable(GL_SCISSOR_TEST);

    glfwSwapBuffers(m_pWindow);
}

void SaWindow_Platform::OnKeyInput(int key, int scanCode, int action, int mods)
{
    if (m_pParent->m_pKeyboardInputHandler)
    {
        if (action == GLFW_PRESS)
        {
            m_pParent->m_pKeyboardInputHandler->OnKeyDown(GetKeyCode(key));
        }
        else if (action == GLFW_RELEASE)
        {
            m_pParent->m_pKeyboardInputHandler->OnKeyUp(GetKeyCode(key));
        }
    }
}

void SaWindow_Platform::KeyInputCallback(GLFWwindow* pWindow, int key, int scanCode, int action, int mods)
{
    for (int windowIdx = 0; windowIdx < MAX_WINDOWS; windowIdx++)
    {
        if (ms_currentWindows[windowIdx] && ms_currentWindows[windowIdx]->m_pWindow == pWindow)
        {
            ms_currentWindows[windowIdx]->OnKeyInput(key, scanCode, action, mods);
            break;
        }
    }
}

SaKeyCode SaWindow_Platform::GetKeyCode(int glfwKeyCode)
{
    switch (glfwKeyCode)
    {
        case GLFW_KEY_ESCAPE: return SA_KEY_ESCAPE;
        case GLFW_KEY_F1: return SA_KEY_F1;
        case GLFW_KEY_F2: return SA_KEY_F2;
        case GLFW_KEY_F3: return SA_KEY_F3;
        case GLFW_KEY_F4: return SA_KEY_F4;
        case GLFW_KEY_F5: return SA_KEY_F5;
        case GLFW_KEY_F6: return SA_KEY_F6;
        case GLFW_KEY_F7: return SA_KEY_F7;
        case GLFW_KEY_F8: return SA_KEY_F8;
        case GLFW_KEY_F9: return SA_KEY_F9;
        case GLFW_KEY_F10: return SA_KEY_F10;
        case GLFW_KEY_F11: return SA_KEY_F11;
        case GLFW_KEY_F12: return SA_KEY_F12;
        case GLFW_KEY_GRAVE_ACCENT: return SA_KEY_GRAVE;
        case GLFW_KEY_1: return SA_KEY_1;
        case GLFW_KEY_2: return SA_KEY_2;
        case GLFW_KEY_3: return SA_KEY_3;
        case GLFW_KEY_4: return SA_KEY_4;
        case GLFW_KEY_5: return SA_KEY_5;
        case GLFW_KEY_6: return SA_KEY_6;
        case GLFW_KEY_7: return SA_KEY_7;
        case GLFW_KEY_8: return SA_KEY_8;
        case GLFW_KEY_9: return SA_KEY_9;
        case GLFW_KEY_0: return SA_KEY_0;
        case GLFW_KEY_MINUS: return SA_KEY_MINUS;
        case GLFW_KEY_EQUAL: return SA_KEY_EQUALS;
        case GLFW_KEY_BACKSPACE: return SA_KEY_BACKSPACE;
        case GLFW_KEY_TAB: return SA_KEY_TAB;
        case GLFW_KEY_Q: return SA_KEY_Q;
        case GLFW_KEY_W: return SA_KEY_W;
        case GLFW_KEY_E: return SA_KEY_E;
        case GLFW_KEY_R: return SA_KEY_R;
        case GLFW_KEY_T: return SA_KEY_T;
        case GLFW_KEY_Y: return SA_KEY_Y;
        case GLFW_KEY_U: return SA_KEY_U;
        case GLFW_KEY_I: return SA_KEY_I;
        case GLFW_KEY_O: return SA_KEY_O;
        case GLFW_KEY_P: return SA_KEY_P;
        case GLFW_KEY_LEFT_BRACKET: return SA_KEY_LEFT_BRACKET;
        case GLFW_KEY_RIGHT_BRACKET: return SA_KEY_RIGHT_BRACKET;
        case GLFW_KEY_BACKSLASH: return SA_KEY_BACK_SLASH;
        case GLFW_KEY_CAPS_LOCK: return SA_KEY_CAPS_LOCK;
        case GLFW_KEY_A: return SA_KEY_A;
        case GLFW_KEY_S: return SA_KEY_S;
        case GLFW_KEY_D: return SA_KEY_D;
        case GLFW_KEY_F: return SA_KEY_F;
        case GLFW_KEY_G: return SA_KEY_G;
        case GLFW_KEY_H: return SA_KEY_H;
        case GLFW_KEY_J: return SA_KEY_J;
        case GLFW_KEY_K: return SA_KEY_K;
        case GLFW_KEY_L: return SA_KEY_L;
        case GLFW_KEY_SEMICOLON: return SA_KEY_SEMI_COLON;
        case GLFW_KEY_APOSTROPHE: return SA_KEY_APOSTROPHE;
        case GLFW_KEY_ENTER: return SA_KEY_RETURN;
        case GLFW_KEY_LEFT_SHIFT: return SA_KEY_LEFT_SHIFT;
        case GLFW_KEY_Z: return SA_KEY_Z;
        case GLFW_KEY_X: return SA_KEY_X;
        case GLFW_KEY_C: return SA_KEY_C;
        case GLFW_KEY_V: return SA_KEY_V;
        case GLFW_KEY_B: return SA_KEY_B;
        case GLFW_KEY_N: return SA_KEY_N;
        case GLFW_KEY_M: return SA_KEY_M;
        case GLFW_KEY_COMMA: return SA_KEY_COMMA;
        case GLFW_KEY_PERIOD: return SA_KEY_PERIOD;
        case GLFW_KEY_SLASH: return SA_KEY_FORWARD_SLASH;
        case GLFW_KEY_RIGHT_SHIFT: return SA_KEY_RIGHT_SHIFT;
        case GLFW_KEY_LEFT_CONTROL: return SA_KEY_LEFT_CTRL;
        case GLFW_KEY_LEFT_SUPER: return SA_KEY_LEFT_OS;
        case GLFW_KEY_LEFT_ALT: return SA_KEY_LEFT_ALT;
        case GLFW_KEY_SPACE: return SA_KEY_SPACE;
        case GLFW_KEY_RIGHT_ALT: return SA_KEY_RIGHT_ALT;
        case GLFW_KEY_RIGHT_SUPER: return SA_KEY_RIGHT_OS;
        case GLFW_KEY_MENU: return SA_KEY_MENU;
        case GLFW_KEY_RIGHT_CONTROL: return SA_KEY_RIGHT_CTRL;
        case GLFW_KEY_PRINT_SCREEN: return SA_KEY_PRINT_SCREEN;
        case GLFW_KEY_SCROLL_LOCK: return SA_KEY_SCROLL_LOCK;
        case GLFW_KEY_PAUSE: return SA_KEY_BREAK;
        case GLFW_KEY_INSERT: return SA_KEY_INSERT;
        case GLFW_KEY_HOME: return SA_KEY_HOME;
        case GLFW_KEY_PAGE_UP: return SA_KEY_PAGE_UP;
        case GLFW_KEY_DELETE: return SA_KEY_DELETE;
        case GLFW_KEY_END: return SA_KEY_END;
        case GLFW_KEY_PAGE_DOWN: return SA_KEY_PAGE_DOWN;
        case GLFW_KEY_UP: return SA_KEY_UP;
        case GLFW_KEY_DOWN: return SA_KEY_DOWN;
        case GLFW_KEY_LEFT: return SA_KEY_LEFT;
        case GLFW_KEY_RIGHT: return SA_KEY_RIGHT;
        case GLFW_KEY_NUM_LOCK: return SA_KEY_NP_NUM_LOCK;
        case GLFW_KEY_KP_DIVIDE: return SA_KEY_NP_DIVIDE;
        case GLFW_KEY_KP_MULTIPLY: return SA_KEY_NP_MULTIPLY;
        case GLFW_KEY_KP_SUBTRACT: return SA_KEY_NP_MINUS;
        case GLFW_KEY_KP_1: return SA_KEY_NP_1;
        case GLFW_KEY_KP_2: return SA_KEY_NP_2;
        case GLFW_KEY_KP_3: return SA_KEY_NP_3;
        case GLFW_KEY_KP_4: return SA_KEY_NP_4;
        case GLFW_KEY_KP_5: return SA_KEY_NP_5;
        case GLFW_KEY_KP_6: return SA_KEY_NP_6;
        case GLFW_KEY_KP_7: return SA_KEY_NP_7;
        case GLFW_KEY_KP_8: return SA_KEY_NP_8;
        case GLFW_KEY_KP_9: return SA_KEY_NP_9;
        case GLFW_KEY_KP_0: return SA_KEY_NP_0;
        case GLFW_KEY_KP_ADD: return SA_KEY_NP_PLUS;
        case GLFW_KEY_KP_DECIMAL: return SA_KEY_NP_DECIMAL;
        case GLFW_KEY_KP_ENTER: return SA_KEY_NP_ENTER;
    }
    
    return SaKeyCode::SA_KEY_UNKNOWN;
}
