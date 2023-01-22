/*************************************************************
Sakura Game Framework : SaKeyboard.cpp
Author: Darrell Blake
*************************************************************/

#include "SaKeyboard.h"
#include <cstring>

using namespace Sakura;

SaKeyboardInputHandler::SaKeyboardInputHandler(SaCallback<SaKeyCode> keyUpFunc, SaCallback<SaKeyCode> keyDownFunc) :
    m_keyUpCallback(keyUpFunc),
    m_keyDownCallback(keyDownFunc)
{
}

void SaKeyboardInputHandler::OnKeyUp(SaKeyCode keyCode) const
{
    m_keyUpCallback(keyCode);
}

void SaKeyboardInputHandler::OnKeyDown(SaKeyCode keyCode) const
{
    m_keyDownCallback(keyCode);
}

SaKeyboard::SaKeyboard() : 
    m_inputHandler(BIND_MEMBER_FUNC(&SaKeyboard::OnKeyUp, this), BIND_MEMBER_FUNC(&SaKeyboard::OnKeyDown, this))
{
    memset(m_keyStates, 0, sizeof(m_keyStates));
}

bool SaKeyboard::IsKeyDown(SaKeyCode keyCode) const
{
    return (m_keyStates[keyCode / 8] & 1 << keyCode % 8) != 0;
}

bool SaKeyboard::IsKeyUp(SaKeyCode keyCode) const
{
    return (m_keyStates[keyCode / 8] & 1 << keyCode % 8) == 0;
}

void SaKeyboard::OnKeyUp(SaKeyCode keyCode)
{
    m_keyStates[keyCode / 8] ^= 1 << keyCode % 8;
}

void SaKeyboard::OnKeyDown(SaKeyCode keyCode)
{
    m_keyStates[keyCode / 8] |= 1 << keyCode % 8;
}
