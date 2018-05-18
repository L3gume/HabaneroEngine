#include <thread>

#include "engine/core/Engine.h"

//
// Following tutorial on:
// http://www.opengl-tutorial.org
//
int main(int argc, char *argv[]) {

    Core::Engine& gm = Core::Engine::getInstance();
    // -----------------------------------------------------------------------------------------------------------------
    // The Game loop runs in a separate thread in order to be able to use the UI at the same time
    // -----------------------------------------------------------------------------------------------------------------
    gm.init();
    gm.gameLoop(true);
    return 0;
}