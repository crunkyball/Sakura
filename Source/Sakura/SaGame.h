/*************************************************************
Sakura Game Framework : SaGame.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_GAME_H
#define _SA_GAME_H

#include "SaCore.h"
#include "SaDebug.h"
#include <Sakura/SaScene.h>
#include "SaGameProperties.h"
#include "SaWindow.h"

namespace Sakura
{
    class SaCamera;

    class SaGame
    {
    public:

        SaGame();
        SaGame(SaGameProperties& rProperties);
        virtual ~SaGame();

        void Run();
        void Quit();

    protected:
        virtual void Initialise();
        virtual void Release();
        virtual void Update(uint32_t dt);
        virtual void PostUpdate();
        virtual void Render3D();    //Split 3D and 2D rendering functions. For 
        virtual void Render2D();    //Render2D depth testing has been disabled.

        const SaGameProperties& GetGameProperties();

        SaWindow& GetWindow() { return m_window; }

    private:
        void WindowCreate();

        bool m_bRunning;
        bool m_bError; //Need something better than this at some point.

        const SaGameProperties m_gameProperties;

        //SaScene m_scene;  //Not using scene yet.
        SaWindow m_window;
    };
}

#endif  //_SA_GAME_H
