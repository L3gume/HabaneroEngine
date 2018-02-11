//
// Created by l3gume on 11/02/18.
//


#include "RenderSystem.h"

RenderSystem::RenderSystem(GLFWwindow *_window, Camera *_cam) : System(), m_window(_window), m_camera(_cam) {
    assert(m_camera != nullptr && m_window != nullptr); // Throw compile time error

    m_priority = 0;

    // TODO: change the path when we are not in DEBUG
    GLuint programID = loadShaders("../shaders/vertex_shader.glsl", "../shaders/fragment_shader.glsl");
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(programID);

    this->matID = glGetUniformLocation(programID, "MVP");

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
}

void RenderSystem::preUpdate(float _deltaTime) {
    m_renderableEntities = Core::Engine::getInstance().getEntityManager().getEntitiesByGroup(
            getComponentTypeID<RenderableComponent>());
    // Update entity list for the update() call.
}

void RenderSystem::update(float _deltaTime) {
    GLuint vertex_buf; // identify the vertex buffer
    glGenBuffers(1, &vertex_buf); // generate 1 buffer

    GLuint vertexArrayID;
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    for (auto &ent : m_renderableEntities) {
        if (ent->hasComponent<RenderableComponent>()) {
            renderEntity(vertex_buf, ent, _deltaTime);
        } else {
            // That's a big problem.
#if DEBUG
            VapeLog::LogManager::getInstance().printMessage(VapeLog::LogMessage(
                    VapeLog::LogTag::RENDER, VapeLog::LogType::WARNING,
                    VapeLog::LogSeverity::CRITICAL, "Entity does not have a RenderableComponent."));
#endif
        }
    }
}

void RenderSystem::renderEntity(GLuint &v_buf, const Entity *_ent, const float _deltaTime) {
    assert(_ent->hasComponent<TransformComponent>());
    const RenderableComponent &comp = _ent->getComponent<RenderableComponent>();
    const TransformComponent &transform = _ent->getComponent<TransformComponent>();
    glm::mat4 translate;
    glm::mat4 rotate;
    glm::mat4 scale;
    glm::mat4 MVP; //MVP matrix

    translate = glm::translate(glm::mat4(1.f), transform.position);
    rotate = glm::toMat4(glm::quat(transform.rotation));
    scale = glm::scale(glm::mat4(1.f), transform.scale);

    if (transform.rotation == glm::vec3(0.f)) rotate = glm::mat4(); // failsafe

    MVP = m_camera->getMVP(_deltaTime, translate * rotate * scale);
    glUniformMatrix4fv(matID, 1, GL_FALSE, &MVP[0][0]);

    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(comp.m_cBuf), comp.m_cBuf, GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(
            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            nullptr                          // array buffer offset
    );

    glBindBuffer(GL_ARRAY_BUFFER, v_buf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(comp.m_vBuf), comp.m_vBuf, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, v_buf);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
}
