//
// Created by notjustin on 12/24/17.
//

#include <cstdio>
#include <renderer/RenderManager.h>
#include <core/Scene.h>
#include <renderer/PrimitiveRenderer.h>
#include <glm/gtc/matrix_transform.hpp>
#include <test_object/Player.h>
#include <imgui/imgui.h>
#include "GameManager.h"
#include "camera/CameraController.h"
#include "loadShaders.h"
#include "LogManager.h"
#include <common/VapeGL.h>
#include "SceneManager.h"
#include <editor/Editor.h>
#include <zconf.h>
#include <wait.h>
#include <thread>

using namespace Vape;

void GameManager::init() {
    // TODO: figure out what the hell I want to do in here.
    m_bInitialized = true;
    m_bShutdown = false;
#if EDITOR
    m_bRunGame = false;
#endif
}

/**
 * Here it is, the game loop.
 * There will be A LOT, and by a lot, I mean A WHOLE LOT more stuff in there.
 */
void GameManager::gameLoop(const bool _editor) {
    if (!isInitialized()) {
#if DEBUG
        fprintf(stderr, "Game Manager is not initialized\n");
#endif
        return;
    }
    m_bRunGame = !_editor;

    // -----------------------------------------------------------------------------------------------------------------
    // GHETTO INITIALIZATION: REMOVE THIS WHEN RENDERING SYSTEM IS DONE
    // -----------------------------------------------------------------------------------------------------------------
#if DEBUG
    printf("DEBUG ENABLED\n");
#endif

    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // OpenGL 3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(x_res, y_res, "VapeEngine", nullptr, nullptr);
    if (!m_window) {
        fprintf(stderr, "Failed to open GLFWwindow.\n");
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(m_window);
//    glewExperimental = (GLboolean) true;
//    if (glewInit() != GLEW_OK) {
//        fprintf(stderr, "Failed to initialize GLEW\n");
//        return;
//    }
    gl3wInit();

    glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);

    /*
     * Initialize Editor UI stuff
     */
    VapeInput::InputManager &inputManager = VapeInput::InputManager::getInstance();
#if EDITOR
    VapeUI::Editor &editor = VapeUI::Editor::getInstance();
    if (!m_bRunGame) {
        editor.init(m_window);
        inputManager.addInputListener(&editor);
    }
#endif

    VapeRenderer::RenderManager &renderManager = VapeRenderer::RenderManager::getInstance();
    renderManager.init();

    Camera c(nullptr, m_window, glm::vec3(0.f, 15.f, 15.f), 3.14f, -0.75f, 45.f);
    c.m_tag = "Camera";


    Core::SceneManager &sceneManager = Core::SceneManager::getInstance();
    inputManager.init(m_window);

#if EDITOR
    CameraController cc(m_window, &c);
    if (!m_bRunGame) {
        inputManager.addInputListener(&cc);
    }
#endif

    // -----------------------------------------------------------------------------------------------------------------
    // GHETTO INITIALIZATION: REMOVE THIS WHEN RENDERING SYSTEM IS DONE
    // -----------------------------------------------------------------------------------------------------------------

    /*
     * The actual loop is here
     */

    Core::Scene *scene = new Core::Scene("Test");

    Core::GameObject cube = Core::GameObject(nullptr);
    cube.addComponent(new VapeRenderer::PrimitiveRenderer(nullptr, VapeRenderer::CUBE));
    Core::Transform *cubeTF = cube.getTransform();
    cubeTF->position = glm::vec3(3.f, 3.f, 0.f);
    cubeTF->scale = glm::vec3(0.5f, 0.5f, 0.5f);
    cube.m_tag = "Cube";

    Player player = Player();
    player.m_tag = "Player";
    player.addComponent(new VapeRenderer::PrimitiveRenderer(nullptr, VapeRenderer::CUBE));
    player.addChild(&cube);
    player.addChild(&c);
    player.getTransform()->position = glm::vec3(2.f, 1.f, 0.f);
    player.getTransform()->scale = glm::vec3(0.5f, 1.f, 0.5f);
    inputManager.addInputListener(&player);
    scene->addObject(&player);

    Core::GameObject plane = Core::GameObject(nullptr);
    plane.m_tag = "Plane";
    plane.addComponent(new VapeRenderer::PrimitiveRenderer(nullptr, VapeRenderer::PLANE));
    Core::Transform *planeTF = plane.getTransform();
    planeTF->scale = glm::vec3(5.f, 1.f, 10.f);

    Core::GameObject pyramid = Core::GameObject(nullptr);
    pyramid.m_tag = "pyramid";
    pyramid.addComponent(new VapeRenderer::PrimitiveRenderer(nullptr, VapeRenderer::PYRAMID));
    Core::Transform *pyramidTF = pyramid.getTransform();
    pyramidTF->position = glm::vec3(2.f, 2.f, 0.f);
    pyramidTF->scale = glm::vec3(1.f, 1.f, 2.f);

    Core::GameObject sphere = Core::GameObject(nullptr);
    sphere.m_tag = "Sphere";
    sphere.addComponent(new VapeRenderer::PrimitiveRenderer(nullptr, VapeRenderer::SPHERE));
    Core::Transform *sphereTF = sphere.getTransform();
    sphereTF->position = glm::vec3(-2.f, 2.f, 0.f);
    sphereTF->scale = glm::vec3(1.f, 1.f, 3.f);

    scene->addObject(&cube);
    scene->addObject(&plane);
    scene->addObject(&pyramid);
    scene->addObject(&sphere);
    scene->addObject(&c);

    Core::SceneManager::getInstance().setActiveScene(scene);

    // TODO: Change the condition lul, The key escape thing breaks the window
    while (!glfwWindowShouldClose(m_window) && !m_bShutdown) {

        if (glfwGetKey(m_window, GLFW_KEY_T) == GLFW_PRESS) {
#if DEBUG
            VapeLog::LogManager::getInstance().printMessage(VapeLog::LogMessage(
                    VapeLog::LogTag::COMMON, VapeLog::LogType::MESSAGE,
                    VapeLog::LogSeverity::CRITICAL, "Testing the logging system."));
#endif
#if EDITOR
            signalRunGame();
#endif
        }

        m_fCurTime = static_cast<float>(glfwGetTime());
        float deltaTime = m_fCurTime - m_fLastTime;
        m_fLastTime = m_fCurTime;

        glfwPollEvents();

        inputManager.update(m_window, deltaTime);
#if EDITOR
        if (!m_bRunGame) {
            cc.update(deltaTime);
        }
#endif

        // C++ 17 :D
        if (const auto activeScene = sceneManager.getActiveScene();
        activeScene != nullptr) {
#if !EDITOR
            activeScene->update(deltaTime);
            // other stuff
#else
            if (m_bRunGame) {
                activeScene->update(deltaTime);
            }
#endif

            renderManager.update(activeScene, m_window, deltaTime, &c);

#if EDITOR
            if (!m_bRunGame) {
                editor.render();
            }
#endif

        }
        glfwSwapBuffers(m_window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
#if EDITOR
    if (!m_bRunGame) {
        editor.shutDown();
    }
#endif
    glfwTerminate();
}

void GameManager::signalRunGame() {
#if EDITOR
//    GameManager gm2;
//    gm2.init();
//    std::thread t([&gm2](){ gm2.gameLoop(false); } );
//    t.join();
#endif
}
