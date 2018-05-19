#include <thread>
#include <windows.h>

#include "engine/core/Engine.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
	PSTR cmdLine, int showCmd){

    Core::Engine& gm = Core::Engine::getInstance();
    // -----------------------------------------------------------------------------------------------------------------
    // The Game loop runs in a separate thread in order to be able to use the UI at the same time
    // -----------------------------------------------------------------------------------------------------------------
    gm.init();
    gm.gameLoop();
    return 0;
}