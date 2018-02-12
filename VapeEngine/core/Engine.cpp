//
// Created by notjustin on 12/24/17.
//

#include <core/Engine.h>
#include <render/RenderSystem.h>
#include <camera/CameraSystem.h>
#include <components/CameraComponent.h>
#include <components/ScriptComponent.h>
#include <script/PlayerMovementScript.h>
#include <script/ScriptSystem.h>

using namespace Core;

void Engine::init() {
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
void Engine::gameLoop(const bool _editor) {
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

    m_systemManager.addSystem<RenderSystem>(m_window);
    m_systemManager.addSystem<CameraSystem>();
    m_systemManager.addSystem<ScriptSystem>();
    m_systemManager.setSystemPriority<ScriptSystem>(100);

    Core::SceneManager &sceneManager = Core::SceneManager::getInstance();
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

    Entity& cube = m_entityManager.addEntity("TestCube");
    cube.addComponent<TransformComponent>(glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f));
    cube.addComponent<RenderableComponent>(VapeRenderer::PrimitiveShapes::CUBE);
    Script *p = new PlayerMovementScript();
    cube.addComponent<ScriptComponent>(p);

    Entity& camera = m_entityManager.addEntity("Camera");
    camera.addComponent<TransformComponent>(glm::vec3(0.f, 15.f, -15.f), glm::vec3(glm::radians(-45.f), 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f));
    camera.addComponent<CameraComponent>(90.f, 16.f, 9.f, 0.1f, 100.f);

    Entity& plane = m_entityManager.addEntity("Plane");
    plane.addComponent<TransformComponent>(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(100.f, 100.f, 100.f));
    plane.addComponent<RenderableComponent>(VapeRenderer::PrimitiveShapes::PLANE);

    // TODO: Change the condition lul, The key escape thing breaks the window
    while (!glfwWindowShouldClose(m_window) && !m_bShutdown) {

        m_fCurTime = static_cast<float>(glfwGetTime());
        float deltaTime = m_fCurTime - m_fLastTime;
        m_fLastTime = m_fCurTime;

        glfwPollEvents();

        m_systemManager.preUpdate(deltaTime); // Call preUpdate on all systems
        //----------------------------------------
        inputManager.update(m_window, deltaTime);
        //----------------------------------------
        m_systemManager.update(deltaTime); // Call update on all systems
        editor.render();
        glfwSwapBuffers(m_window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_systemManager.postUpdate(deltaTime); // Is called after rendering

    }
#if EDITOR
    editor.shutDown();
#endif
    glfwTerminate();
}

void Engine::signalRunGame() {
#if EDITOR
//    Core::SceneManager &sceneManager = Core::SceneManager::getInstance();
//    if (!m_bRunGame) {
////        m_tempScene = new Scene(*(sceneManager.getActiveScene()));// Make a copy of the current active scene
////        if (m_tempScene != nullptr) {
////            delete m_tempScene;
////            m_tempScene = nullptr;
////        }
//        m_tempScene = sceneManager.getActiveScene()->createBackup();
////        sceneManager.backupActiveScene(); // Push the active onto the stack
////        sceneManager.setActiveScene(m_tempScene); // Make active scene point to the copied version
//    } else {
////        delete sceneManager.getActiveScene();
//        sceneManager.setActiveScene(m_tempScene);
//        delete m_tempScene;
////        sceneManager.restorePreviousScene();
//    }
    m_bRunGame = !m_bRunGame;
#endif
}
