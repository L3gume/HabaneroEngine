#include <GameManager.h>
#include <thread>
#include "LogManager.h"

//
// Following tutorial on:
// http://www.opengl-tutorial.org
//
int main(int argc, char *argv[]) {

    Vape::GameManager& gm = Vape::GameManager::getInstance();
    VapeLog::LogManager& lm = VapeLog::LogManager::getInstance();
    // -----------------------------------------------------------------------------------------------------------------
    // The Game loop runs in a separate thread in order to be able to use the UI at the same time
    // -----------------------------------------------------------------------------------------------------------------
    gm.init();
    gm.gameLoop(true);
    return 0;
}