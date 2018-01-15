#include <GameManager.h>
#include <QtWidgets/QApplication>
#include <thread>
#include "logger.h"
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
    std::thread game([&gm](){gm.gameLoop();});
    game.detach();

    QApplication a(argc, argv);
    VapeLog::Logger w(nullptr);
    lm.setLogger(&w);
    w.show();
    a.exec();

    return 0;
}