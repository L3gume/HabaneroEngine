#include <Engine.h>
#include <thread>
#include "LogManager.h"

//
// Following tutorial on:
// http://www.opengl-tutorial.org
//
int main(int argc, char *argv[]) {
    Core::Engine& gm = Core::Engine::getInstance();
    VapeLog::LogManager& lm = VapeLog::LogManager::getInstance();
    gm.init();
    gm.gameLoop(true);
    return 0;
}