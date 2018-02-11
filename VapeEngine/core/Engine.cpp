//
// Created by notjustin on 12/24/17.
//

#include <core/Engine.h>
#include <render/RenderSystem.h>

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

//    VapeRenderer::RenderManager &renderManager = VapeRenderer::RenderManager::getInstance();
//    renderManager.init();

    Camera c(nullptr, m_window, glm::vec3(0.f, 15.f, 15.f), 3.14f, -0.75f, 45.f);
    c.m_tag = "EditorCamera";

    m_systemManager.addSystem<RenderSystem>(m_window, &c);

    Core::SceneManager &sceneManager = Core::SceneManager::getInstance();
    inputManager.init(m_window);

//#if EDITOR
//    CameraController cc(m_window, &c);
//    if (!m_bRunGame) {
//        inputManager.addInputListener(&cc);
//    }
//#endif

    // -----------------------------------------------------------------------------------------------------------------
    // GHETTO INITIALIZATION: REMOVE THIS WHEN RENDERING SYSTEM IS DONE
    // -----------------------------------------------------------------------------------------------------------------

    /*
     * The actual loop is here
     */

//    Core::Scene *scene = new Core::Scene("Test");
//
//    Core::GameObject cube = Core::GameObject(nullptr);
//    cube.addComponent(new VapeRenderer::PrimitiveRenderer(nullptr, VapeRenderer::CUBE));
//    Core::Transform *cubeTF = cube.getTransform();
//    cubeTF->position = glm::vec3(3.f, 3.f, 0.f);
//    cubeTF->scale = glm::vec3(0.5f, 0.5f, 0.5f);
//    cube.m_tag = "Cube";
//
//    Camera c2(nullptr, m_window, glm::vec3(0.f, 15.f, 15.f), 3.14f, -0.75f, 45.f);
//    c2.m_tag = "SceneCamera";
//
//    Player player = Player();
//    player.m_tag = "Player";
//    player.addComponent(new VapeRenderer::PrimitiveRenderer(nullptr, VapeRenderer::CUBE));
//    player.addChild(&cube);
//    player.addChild(&c2);
//    player.getTransform()->position = glm::vec3(2.f, 1.f, 0.f);
//    player.getTransform()->scale = glm::vec3(0.5f, 1.f, 0.5f);
//    inputManager.addInputListener(&player);
//    scene->addObject(&player);
//
//    Core::GameObject plane = Core::GameObject(nullptr);
//    plane.m_tag = "Plane";
//    plane.addComponent(new VapeRenderer::PrimitiveRenderer(nullptr, VapeRenderer::PLANE));
//    Core::Transform *planeTF = plane.getTransform();
//    planeTF->scale = glm::vec3(5.f, 1.f, 10.f);
//
//    Core::GameObject pyramid = Core::GameObject(nullptr);
//    pyramid.m_tag = "pyramid";
//    pyramid.addComponent(new VapeRenderer::PrimitiveRenderer(nullptr, VapeRenderer::PYRAMID));
//    Core::Transform *pyramidTF = pyramid.getTransform();
//    pyramidTF->position = glm::vec3(2.f, 2.f, 0.f);
//    pyramidTF->scale = glm::vec3(1.f, 1.f, 2.f);
//
//    Core::GameObject sphere = Core::GameObject(nullptr);
//    sphere.m_tag = "Sphere";
//    sphere.addComponent(new VapeRenderer::PrimitiveRenderer(nullptr, VapeRenderer::SPHERE));
//    Core::Transform *sphereTF = sphere.getTransform();
//    sphereTF->position = glm::vec3(-2.f, 2.f, 0.f);
//    sphereTF->scale = glm::vec3(1.f, 1.f, 3.f);
//
//    scene->addObject(&cube);
//    scene->addObject(&plane);
//    scene->addObject(&pyramid);
//    scene->addObject(&sphere);
//    scene->addObject(&c2);
//    scene->setCamera(&c2);
//
//    Core::SceneManager::getInstance().setActiveScene(scene);
    Entity& cube = m_entityManager.addEntity("TestCube");
    cube.addComponent<TransformComponent>(glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f));
    cube.addComponent<RenderableComponent>(VapeRenderer::PrimitiveShapes::CUBE);

    // TODO: Change the condition lul, The key escape thing breaks the window
    while (!glfwWindowShouldClose(m_window) && !m_bShutdown) {

        m_fCurTime = static_cast<float>(glfwGetTime());
        float deltaTime = m_fCurTime - m_fLastTime;
        m_fLastTime = m_fCurTime;

        glfwPollEvents();

        m_systemManager.preUpdate(deltaTime); // Call preUpdate on all systems
        m_systemManager.update(deltaTime); // Call update on all systems
        glfwSwapBuffers(m_window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_systemManager.postUpdate(deltaTime); // Is called after rendering

//        inputManager.update(m_window, deltaTime);
//#if EDITOR
//        if (!m_bRunGame) {
//            cc.update(deltaTime);
//        }
//#endif
//
//        if (const auto activeScene = sceneManager.getActiveScene();
//        activeScene != nullptr) {
//#if !EDITOR
//            activeScene->update(deltaTime);
//            renderManager.update(activeScene, m_window, deltaTime, activeScene->getCamera());
//#else
//            if (!m_bRunGame) {
//                renderManager.update(activeScene, m_window, deltaTime, &c);
//                editor.render();
//            } else {
//                activeScene->update(deltaTime);
//                renderManager.update(activeScene, m_window, deltaTime, activeScene->getCamera());
//            }
//#endif
//
//        }

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
