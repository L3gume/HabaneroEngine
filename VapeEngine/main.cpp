#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/matrix.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <InputManager.h>
#include <GameManager.h>
#include <QtWidgets/QApplication>
#include <thread>

#include "common/loadShaders.h"
#include "common/CameraController.h"
#include "logger.h"

//
// Following tutorial on:
// http://www.opengl-tutorial.org
//
int main(int argc, char *argv[]) {

    Vape::GameManager& gm = Vape::GameManager::getInstance();

    // -----------------------------------------------------------------------------------------------------------------
    // The Game loop runs in a separate thread in order to be able to use the UI at the same time
    // -----------------------------------------------------------------------------------------------------------------
    gm.init();
    std::thread game([&gm](){gm.gameLoop();});
    game.detach();

    QApplication a(argc, argv);
    VapeLog::Logger w(nullptr);
    w.show();
    a.exec();

    return 0;
}