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
#include <components/BoxColliderComponent.h>
#include <systems/CollisionSystem.h>
#include <components/ColliderComponent.h>
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
    m_systemManager.addSystem<CollisionSystem>();
    m_systemManager.setSystemPriority<CollisionSystem>(80);

    inputManager.init(m_window);

    // -----------------------------------------------------------------------------------------------------------------
    // GHETTO INITIALIZATION: REMOVE THIS WHEN RENDERING SYSTEM IS DONE
    // -----------------------------------------------------------------------------------------------------------------

    /*
     * The actual loop is here
     */

    SceneManager& scnMan = SceneManager::getInstance();
//    scnMan.loadScene("bugFree.scn");

    auto& player = m_entityManager.addEntity("Player");
    player.addComponent<TransformComponent>(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f));
    player.addComponent<RenderableComponent>(VapeRenderer::PrimitiveShapes::CUBE);
    player.addComponent<ScriptComponent>(new PlayerMovementScript());
    auto& transform = player.getComponent<TransformComponent>();
//    player.addComponent<BoxColliderComponent>(transform.position, transform.scale);
//    player.addComponent<ColliderComponent>(transform.position, transform.scale, false, false);
    player.addComponent<ColliderComponent>(transform.position, 2.f, false, false);

    auto& wall = m_entityManager.addEntity("wall");
    wall.addComponent<TransformComponent>(glm::vec3(0.f, 0.f, 5.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(5.f, 3.f, 1.f));
    wall.addComponent<RenderableComponent>(VapeRenderer::PrimitiveShapes::CUBE);
    auto& transform2 = wall.getComponent<TransformComponent>();
//    auto& box = wall.addComponent<BoxColliderComponent>(transform2.position, transform2.scale);
    auto& box = wall.addComponent<ColliderComponent>(transform2.position, transform2.scale, false, false);
//    box.isStatic = true;

    auto& cam = m_entityManager.addEntity("cam");
    cam.addComponent<TransformComponent>(glm::vec3(0.f, 15.f, 5.f), glm::vec3(90.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f));
    cam.addComponent<CameraComponent>(90.f, 16.f, 9.f, 0.1f, 100.f);
#if EDITOR
    m_systemManager.switchMode(false);
#endif
    while (!glfwWindowShouldClose(m_window) && !m_bShutdown) {

        m_fCurTime = static_cast<float>(glfwGetTime());
        float deltaTime = m_fCurTime - m_fLastTime;
        m_fLastTime = m_fCurTime;

        glfwPollEvents();

        m_systemManager.preUpdate(deltaTime); // Call preUpdate on all systems
        //----------------------------------------
        inputManager.update(m_window, deltaTime); // get inputs.
        //----------------------------------------
        m_systemManager.update(deltaTime); // Call update on all systems
#if EDITOR
        if (!m_bRunGame) editor.render(); // Editor stuff
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
        m_systemManager.switchMode(!m_bRunGame);
        InputManager::getInstance().switchMode(!m_bRunGame);
#if DEBUG
        VapeLog::LogManager::getInstance().printMessage(VapeLog::LogMessage(
                VapeLog::LogTag::GAME, VapeLog::LogType::MESSAGE,
                VapeLog::LogSeverity::LOW, "Switched to Game Mode!"));
#endif
    } else {
        reset();
        VapeUI::Editor::getInstance().reset();
        sm.restoreScene();
        m_systemManager.switchMode(!m_bRunGame);
        InputManager::getInstance().switchMode(!m_bRunGame);
#if DEBUG
        VapeLog::LogManager::getInstance().printMessage(VapeLog::LogMessage(
                VapeLog::LogTag::GAME, VapeLog::LogType::MESSAGE,
                VapeLog::LogSeverity::LOW, "Switched to Editor Mode!"));
#endif
    }
    m_bRunGame = !m_bRunGame;
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
    m_systemManager.addSystem<CollisionSystem>();
    m_systemManager.setSystemPriority<CollisionSystem>(80);
    m_entityManager = ECS::EntityManager(); // reset manager
#if EDITOR
    m_systemManager.switchMode(m_bRunGame);
    InputManager::getInstance().switchMode(m_bRunGame);
#endif
}
