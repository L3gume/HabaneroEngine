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
#include "VapeGL.h"
#include "SceneManager.h"
#include <imgui_impl_glfw_gl3.h>

using namespace Vape;

void GameManager::init() {
    // TODO: figure out what the hell I want to do in here.
    m_bInitialized = true;
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

    m_window = glfwCreateWindow(1280, 720, "VapeEngine", nullptr, nullptr);
    if (!m_window) {
        fprintf(stderr, "Failed to open GLFWwindow.\n");
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(m_window);
    glewExperimental = (GLboolean) true;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return;
    }

    glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);

    /*
     * Initialize Editor UI stuff
     */
#if EDITOR
    ImGui_ImplGlfwGL3_Init(m_window, true);

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    // Setup style
    ImGui::StyleColorsDark();
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize.x = 1280.0f;
    io.DisplaySize.y = 720.0f;
    io.RenderDrawListsFn = nullptr;  // Setup a render function, or set to NULL and call GetDrawData() after Render() to access render data.
    // TODO: Fill others settings of the io structure later.

    // Load texture atlas (there is a default font so you don't need to care about choosing a font yet)
    unsigned char* pixels;
    int width, height;
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
    // TODO: At this points you've got the texture data and you need to upload that your your graphic system:
//    MyTexture* texture = MyEngine::CreateTextureFromMemoryPixels(pixels, width, height, TEXTURE_TYPE_RGBA);
    // TODO: Store your texture pointer/identifier (whatever your engine uses) in 'io.Fonts->TexID'. This will be passed back to your via the renderer.
//    io.Fonts->TexID = (void*)texture;
#endif

    VapeRenderer::RenderManager& renderManager = VapeRenderer::RenderManager::getInstance();
    renderManager.init();

    Camera c(nullptr, m_window, glm::vec3(0.f, 15.f, 15.f), 3.14f, -0.75f, 45.f);
    c.m_tag = "Camera";
    CameraController cc(m_window, &c);
    VapeInput::InputManager& inputManager = VapeInput::InputManager::getInstance();
    Core::SceneManager& sceneManager = Core::SceneManager::getInstance();
    inputManager.init(m_window);
    inputManager.addInputListener(&cc);

    // -----------------------------------------------------------------------------------------------------------------
    // GHETTO INITIALIZATION: REMOVE THIS WHEN RENDERING SYSTEM IS DONE
    // -----------------------------------------------------------------------------------------------------------------

    /*
     * The actual loop is here
     */

    Core::Scene* scene = new Core::Scene("Test");

    Core::GameObject cube = Core::GameObject(nullptr);
    cube.addComponent(new VapeRenderer::PrimitiveRenderer(nullptr, VapeRenderer::CUBE));
    Core::Transform* cubeTF = cube.getTransform();
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
    "Plane";
    plane.addComponent(new VapeRenderer::PrimitiveRenderer(nullptr, VapeRenderer::PLANE));
    Core::Transform* planeTF = plane.getTransform();
    planeTF->scale = glm::vec3(5.f, 1.f, 10.f);

    Core::GameObject pyramid = Core::GameObject(nullptr);
    pyramid.addComponent(new VapeRenderer::PrimitiveRenderer(nullptr, VapeRenderer::PYRAMID));
    Core::Transform* pyramidTF = pyramid.getTransform();
    pyramidTF->position = glm::vec3(2.f, 2.f, 0.f);
    pyramidTF->scale = glm::vec3(1.f, 1.f, 2.f);

    Core::GameObject sphere = Core::GameObject(nullptr);
    sphere.addComponent(new VapeRenderer::PrimitiveRenderer(nullptr, VapeRenderer::SPHERE));
    Core::Transform* sphereTF = sphere.getTransform();
    sphereTF->position = glm::vec3(-2.f, 2.f, 0.f);
    sphereTF->scale = glm::vec3(1.f, 1.f, 3.f);

    scene->addObject(&cube);
    scene->addObject(&plane);
    scene->addObject(&pyramid);
    scene->addObject(&sphere);
    scene->addObject(&c);

    Core::SceneManager::getInstance().setActiveScene(scene);

    // TODO: Change the condition lul, The key escape thing breaks the window
    while (!glfwWindowShouldClose(m_window)) {

        if (glfwGetKey(m_window, GLFW_KEY_T) == GLFW_PRESS) {
#if DEBUG
            fprintf(stderr, "Message sent to logger\n");
#endif
            VapeLog::LogManager::getInstance().printMessage(VapeLog::LogMessage(
                    VapeLog::LogTag::COMMON, VapeLog::LogType::MESSAGE,
                    VapeLog::LogSeverity::CRITICAL, "Testing the logging system."));
        }



        m_fCurTime = static_cast<float>(glfwGetTime());
        float deltaTime = m_fCurTime - m_fLastTime;
        m_fLastTime = m_fCurTime;

#if EDITOR
        ImGuiIO& io = ImGui::GetIO();
        io.DeltaTime = deltaTime;
        float x, y;

        ImGui_ImplGlfwGL3_NewFrame();
        static float f = 0.0f;
        static int counter = 0;
        ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our windows open/close state
        ImGui::Checkbox("Another Window", &show_another_window);

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
// 3. Show the ImGui demo window. Most of the sample code is in ImGui::ShowDemoWindow(). Read its code to learn more about Dear ImGui!
        if (show_demo_window)
        {
            ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver); // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. Here we just want to make the demo initial state a bit more friendly!
            ImGui::ShowDemoWindow(&show_demo_window);
        }
#endif

        inputManager.update(m_window, deltaTime);
        cc.update(deltaTime);

        // C++ 17 :D
        if (const auto activeScene = sceneManager.getActiveScene(); activeScene != nullptr) {
#if EDITOR
            // Rendering
            int display_w, display_h;
            glfwGetFramebufferSize(m_window, &display_w, &display_h);
            glViewport(0, 0, display_w / 2, display_h / 2);
            glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui::Render();
#else
            activeScene->update(deltaTime);
#endif
            renderManager.update(activeScene, m_window, deltaTime, &c);
        }
    }
}
