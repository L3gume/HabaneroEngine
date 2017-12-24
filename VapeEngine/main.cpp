#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/matrix.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <InputManager.h>
#include <GameManager.h>

#include "common/loadShaders.h"
#include "common/CameraController.h"

//
// Following tutorial on:
// http://www.opengl-tutorial.org
//
int main() {

    Vape::GameManager& gm = Vape::GameManager::getInstance();
    gm.init();
    gm.gameLoop();

    return 0;
}