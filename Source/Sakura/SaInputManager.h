/*************************************************************
Sakura Game Framework : SaInputManager.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_INPUT_MANAGER_H
#define _SA_INPUT_MANAGER_H

#include "SaCore.h"
#include "SaKeyboard.h"

namespace Sakura
{
    class SaInputManager
    {
    public:
        static void Initialise();
        static void Release();

        static const SaKeyboard& GetKeyboard() { return m_keyboard; }

    private:
        static SaKeyboard m_keyboard;
    };
}

#endif  //_SA_INPUT_MANAGER_H
