/*************************************************************
Sakura Game Framework : SaKeyboard.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_KEYBOARD_H
#define _SA_KEYBOARD_H

#include "SaCore.h"
#include "SaCallback.h"

namespace Sakura
{
    //These keycodes are listed by row based on the standard 104 keyboard layout.
    //This can be extended, if more are required.
    enum SaKeyCode
    {
        SA_KEY_UNKNOWN = -1,

        //Left side of the keyboard:

        //Top row.
        SA_KEY_ESCAPE,
        SA_KEY_F1,
        SA_KEY_F2,
        SA_KEY_F3,
        SA_KEY_F4,
        SA_KEY_F5,
        SA_KEY_F6,
        SA_KEY_F7,
        SA_KEY_F8,
        SA_KEY_F9,
        SA_KEY_F10,
        SA_KEY_F11,
        SA_KEY_F12,

        //First row.
        SA_KEY_GRAVE,
        SA_KEY_1,
        SA_KEY_2,
        SA_KEY_3,
        SA_KEY_4,
        SA_KEY_5,
        SA_KEY_6,
        SA_KEY_7,
        SA_KEY_8,
        SA_KEY_9,
        SA_KEY_0,
        SA_KEY_MINUS,
        SA_KEY_EQUALS,
        SA_KEY_BACKSPACE,

        //Second row.
        SA_KEY_TAB,
        SA_KEY_Q,
        SA_KEY_W,
        SA_KEY_E,
        SA_KEY_R,
        SA_KEY_T,
        SA_KEY_Y,
        SA_KEY_U,
        SA_KEY_I,
        SA_KEY_O,
        SA_KEY_P,
        SA_KEY_LEFT_BRACKET,
        SA_KEY_RIGHT_BRACKET,
        SA_KEY_BACK_SLASH,

        //Third row.
        SA_KEY_CAPS_LOCK,
        SA_KEY_A,
        SA_KEY_S,
        SA_KEY_D,
        SA_KEY_F,
        SA_KEY_G,
        SA_KEY_H,
        SA_KEY_J,
        SA_KEY_K,
        SA_KEY_L,
        SA_KEY_SEMI_COLON,
        SA_KEY_APOSTROPHE,
        SA_KEY_RETURN,

        //Fourth row.
        SA_KEY_LEFT_SHIFT,
        SA_KEY_Z,
        SA_KEY_X,
        SA_KEY_C,
        SA_KEY_V,
        SA_KEY_B,
        SA_KEY_N,
        SA_KEY_M,
        SA_KEY_COMMA,
        SA_KEY_PERIOD,
        SA_KEY_FORWARD_SLASH,
        SA_KEY_RIGHT_SHIFT,

        //Fifth row.
        SA_KEY_LEFT_CTRL,
        SA_KEY_LEFT_OS,
        SA_KEY_LEFT_ALT,
        SA_KEY_SPACE,
        SA_KEY_RIGHT_ALT,
        SA_KEY_RIGHT_OS,
        SA_KEY_MENU,
        SA_KEY_RIGHT_CTRL,


        //Right side of the keyboard:

        //Top keys.
        SA_KEY_PRINT_SCREEN,
        SA_KEY_SCROLL_LOCK,
        SA_KEY_BREAK,

        //Middle keys.
        SA_KEY_INSERT,
        SA_KEY_HOME,
        SA_KEY_PAGE_UP,
        SA_KEY_DELETE,
        SA_KEY_END,
        SA_KEY_PAGE_DOWN,

        //Cursor keys.
        SA_KEY_UP,
        SA_KEY_DOWN,
        SA_KEY_LEFT,
        SA_KEY_RIGHT,

        //Numpad.
        SA_KEY_NP_NUM_LOCK,
        SA_KEY_NP_DIVIDE,
        SA_KEY_NP_MULTIPLY,
        SA_KEY_NP_MINUS,
        SA_KEY_NP_1,
        SA_KEY_NP_2,
        SA_KEY_NP_3,
        SA_KEY_NP_4,
        SA_KEY_NP_5,
        SA_KEY_NP_6,
        SA_KEY_NP_7,
        SA_KEY_NP_8,
        SA_KEY_NP_9,
        SA_KEY_NP_0,
        SA_KEY_NP_PLUS,
        SA_KEY_NP_DECIMAL,
        SA_KEY_NP_ENTER,

        SA_KEY_MAX
    };

    class SaKeyboardInputHandler
    {
        public:
            SaKeyboardInputHandler(SaCallback<SaKeyCode> keyUpFunc, SaCallback<SaKeyCode> keyDownFunc);

            void OnKeyDown(SaKeyCode keyCode) const;
            void OnKeyUp(SaKeyCode keyCode) const;

        private:
            SaCallback<SaKeyCode> m_keyUpCallback;
            SaCallback<SaKeyCode> m_keyDownCallback;
    };

    class SaKeyboard
    {
    public:
        SaKeyboard();

        const SaKeyboardInputHandler& GetInputHandler() const { return m_inputHandler; }

        bool IsKeyDown(SaKeyCode keyCode) const;
        bool IsKeyUp(SaKeyCode keyCode) const;

    private:
        void OnKeyUp(SaKeyCode keyCode);
        void OnKeyDown(SaKeyCode keyCode);

        SaKeyboardInputHandler m_inputHandler;

        uint8_t m_keyStates[NUM_BITS<SA_KEY_MAX>::Value];
    };
}

#endif  //_SA_KEYBOARD_H
