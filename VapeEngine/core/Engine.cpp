//
// Created by notjustin on 12/24/17.
//

#include <core/Engine.h>
#include <systems/RenderSystem.h>
#include <systems/CameraSystem.h>
#include <components/CameraComponent.h>
#include <components/ScriptComponent.h>
#include <script/PlayerMovementScript.h>
#include <systems/ScriptSystem.h>
#include <ecs/EntityConstructor.h>
#include <systems/TransformSystem.h>
#include "SceneManager.h"

using namespace Core;

void Engine::init() {
    // TODO: figure out what the hell I want to do in here.
    // TODO: Configs (file paths)
    m_bInitialized = true;
    m_bShutdown = false;
#if EDITOR
    m_bRunGame = false;
    m_bSwitchMode = false;
#endif
}

/**
 * Here it is, the game loop.
 * There will be A LOT, and by a lot, I mean A WHOLE LOT more stuff in there.
 */
void Engine::gameLoop(const bool _editor) {
    if (!isInitialized()) {
#if DEBUG
        fprintf(stderr, "Game Manager is not initialized\n");
#endif
        return;
    }
#if EDITOR
    m_bRunGame = !_editor;
#endif
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
    gl3wInit();

    glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);

    /*
     * Initialize Editor UI stuff
     */
    VapeInput::InputManager &inputManager = VapeInput::InputManager::getInstance();
#if EDITOR
    VapeUI::Editor &editor = VapeUI::Editor::getInstance();
    m_freeCam = EditorCamera(m_window);
    inputManager.addInputListener(&m_freeCam);
    if (!m_bRunGame) {
        editor.init(m_window);
        inputManager.addInputListener(&editor);
    }
#endif

    m_systemManager.addSystem<RenderSystem>(m_window);
    m_systemManager.addSystem<CameraSystem>();
    m_systemManager.addSystem<ScriptSystem>();
    m_systemManager.setSystemPriority<ScriptSystem>(100);
    m_systemManager.addSystem<TransformSystem>();
    m_systemManager.setSystemPriority<TransformSystem>(90);

    inputManager.init(m_window);

#if EDITOR
//    CameraController cc(m_window, &c);
    if (!m_bRunGame) {
//        inputManager.addInputListener(&cc);
    }
#endif

    // -----------------------------------------------------------------------------------------------------------------
    // GHETTO INITIALIZATION: REMOVE THIS WHEN RENDERING SYSTEM IS DONE
    // -----------------------------------------------------------------------------------------------------------------

    /*
     * The actual loop is here
     */

//    m_entityManager.loadEntity("cube.ent");
//    m_entityManager.loadEntity("camera.ent");
//    m_entityManager.loadEntity("plane.ent");
//    m_entityManager.loadEntity("testparent.ent");
//    Entity& test = m_entityManager.addEntity("testPlane");
//    test.addComponent<TransformComponent>(glm::vec3(0.f, 0.f, 0.f), glm::vec3(glm::radians(90.f), 0.f, 0.f), glm::vec3(10.f, 10.f, 10.f));
//    test.addComponent<RenderableComponent>(VapeRenderer::PrimitiveShapes::PLANE);
//    EntityConstructor c;
//    c.saveEntity(test, "test.ent");

//    m_entityManager.loadEntity("test.ent");
    SceneManager& scnMan = SceneManager::getInstance();
//    scnMan.saveScene("testScene");
    scnMan.loadScene("testScene.scn");
//    scnMan.loadScene("testPlaneScene.scn");
#if EDITOR
    m_systemManager.switchMode(false);
#endif
    // TODO: Change the condition lul, The key escape thing breaks the window
    while (!glfwWindowShouldClose(m_window) && !m_bShutdown) {

        m_fCurTime = static_cast<float>(glfwGetTime());
        float deltaTime = m_fCurTime - m_fLastTime;
        m_fLastTime = m_fCurTime;

//        float fps = 1 / deltaTime;
//        std::stringstream s;
//        s << fps << "    " << deltaTime;
//
//#if DEBUG
//        VapeLog::LogManager::getInstance().printMessage(VapeLog::LogMessage(
//                VapeLog::LogTag::LOG, VapeLog::LogType::MESSAGE,
//                VapeLog::LogSeverity::LOW, s.str()));
//#endif

        glfwPollEvents();

        m_systemManager.preUpdate(deltaTime); // Call preUpdate on all systems
        //----------------------------------------
        inputManager.update(m_window, deltaTime);
//        if (glfwGetKey(m_window, GLFW_KEY_0)) m_bSwitchMode = true;
        //----------------------------------------
        m_systemManager.update(deltaTime); // Call update on all systems
#if EDITOR
        if (!m_bRunGame) editor.render();
#endif
        glfwSwapBuffers(m_window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_systemManager.postUpdate(deltaTime); // Is called after rendering

        if (m_bSwitchMode) switchMode();
    }
#if EDITOR
    editor.shutDown();
#endif
    glfwTerminate();
}

void Engine::switchMode() {
#if EDITOR
    SceneManager& sm = SceneManager::getInstance();
    if (!m_bRunGame) {
        sm.backupScene();
//        sm.saveScene("testScene.scn");
        m_systemManager.switchMode(!m_bRunGame);
#if DEBUG
        VapeLog::LogManager::getInstance().printMessage(VapeLog::LogMessage(
                VapeLog::LogTag::GAME, VapeLog::LogType::MESSAGE,
                VapeLog::LogSeverity::LOW, "Switched to Game Mode!"));
#endif
    } else {
//        m_systemManager.disableAllSystems();
//        m_systemManager.getSystem<CameraSystem>()->setActiveCamera(nullptr);
        reset();
        VapeUI::Editor::getInstance().reset();
        sm.restoreScene();
//        sm.loadScene("testScene.scn");
        m_systemManager.switchMode(!m_bRunGame);
#if DEBUG
        VapeLog::LogManager::getInstance().printMessage(VapeLog::LogMessage(
                VapeLog::LogTag::GAME, VapeLog::LogType::MESSAGE,
                VapeLog::LogSeverity::LOW, "Switched to Editor Mode!"));
#endif
    }
    m_bRunGame = !m_bRunGame;
//    m_systemManager.switchMode(m_bRunGame);
    m_bSwitchMode = false;
#endif
}

void Engine::signalRunGame() {
    m_bSwitchMode = true;
}

void Engine::reset() {
    m_systemManager = ECS::SystemManager();
    m_systemManager.addSystem<RenderSystem>(m_window);
    m_systemManager.addSystem<CameraSystem>();
    m_systemManager.addSystem<ScriptSystem>();
    m_systemManager.setSystemPriority<ScriptSystem>(100);
    m_systemManager.addSystem<TransformSystem>();
    m_systemManager.setSystemPriority<TransformSystem>(90);
    m_entityManager = ECS::EntityManager(); // reset manager
}
