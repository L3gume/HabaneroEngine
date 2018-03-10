//TODO: Why does it crash immediately lol


#include <render/util/texture.h>
#include <render/util/objloader.h>
#include <render/util/vboindexer.h>
#include "RenderSystem.h"

RenderSystem::RenderSystem(GLFWwindow *_window/*, Camera *_cam*/) : System(), m_window(_window)/*, m_camera(_cam)*/{
    assert(/*m_camera != nullptr && */m_window != nullptr); // Throw compile time error

    m_priority = 0;

    // TODO: change the path when we are not in DEBUG
    this->programID = loadShaders("../shaders/model_vertex_shader.glsl", "../shaders/model_fragment_shader.glsl");

    this->matID = glGetUniformLocation(this->programID, "MVP");
    this->viewID = glGetUniformLocation(this->programID, "V");
    this->modID = glGetUniformLocation(this->programID, "M");

    this->textureID = glGetUniformLocation(this->programID, "myTextureSampler");

    glGenBuffers(1, &this->vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);

    glGenBuffers(1, &this->uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->uvBuffer);

    glGenBuffers(1, &this->normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->normalBuffer);

    glGenBuffers(1, &this->elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->elementBuffer);

    glUseProgram(this->programID);
    this->lightID = glGetUniformLocation(this->programID, "LightPosition_worldspace");

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

#if EDITOR
    m_enabledInEditorMode = true;
#endif
}

void RenderSystem::preUpdate(float _deltaTime) {
    m_renderableEntities = Core::Engine::getInstance().getEntityManager().getEntitiesByGroup(
            getComponentTypeID<RenderableComponent>());
    // Update entity list for the update() call.
}

void RenderSystem::update(float _deltaTime) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
    glUseProgram(programID);

    assert(_ent->hasComponent<TransformComponent>());
    RenderableComponent &comp = _ent->getComponent<RenderableComponent>();
    const TransformComponent &transform = _ent->getComponent<TransformComponent>();
    glm::mat4 translate;
    glm::mat4 rotate;
    glm::mat4 scale;
    glm::mat4 MVP; //MVP matrix

    //Render relative to parent if one exists
    if (!_ent->getParent()) {
        translate = glm::translate(glm::mat4(1.f), transform.position);
        rotate = glm::toMat4(glm::quat(transform.rotation));
        scale = glm::scale(glm::mat4(1.f), transform.scale);
    } else {
        translate = glm::translate(glm::mat4(1.f), transform.abs_position);
        rotate = glm::toMat4(glm::quat(transform.abs_rotation));
        scale = glm::scale(glm::mat4(1.f), transform.abs_scale);
    }

    if (transform.rotation == glm::vec3(0.f) && !_ent->getParent()) rotate = glm::mat4(); // failsafe

//    MVP = m_camera->getMVP(_deltaTime, translate * rotate * scale);
#if !EDITOR
    MVP = Core::Engine::getInstance().getSystemManager().getSystem<CameraSystem>()->getMVPFromActiveCamera(
            translate * rotate * scale);
#else
    MVP = Core::Engine::getInstance().gameRunning() ?
          Core::Engine::getInstance().getSystemManager().getSystem<CameraSystem>()->getMVPFromActiveCamera(
                    translate * rotate * scale) :
          Core::Engine::getInstance().getEditorCam().getMVP(_deltaTime, translate * rotate * scale);
#endif

    if (!comp.getLoaded()) { //Only load texture once
        GLuint texture = loadDDS(reinterpret_cast<const char *>(comp.getTexturePath()));
        m_textures.push_back(texture);
        comp.setTextureID(m_textures.size() - 1);
        comp.setLoaded(true);
    }

    // Read our .obj file
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    bool res = loadOBJ(reinterpret_cast<const char *>(comp.getModelPath()), vertices, uvs, normals);

    std::vector<unsigned short> indices;
    std::vector<glm::vec3> indexed_vertices;
    std::vector<glm::vec2> indexed_uvs;
    std::vector<glm::vec3> indexed_normals;
    indexVBO(vertices, uvs, normals, indices, indexed_vertices, indexed_uvs, indexed_normals);

    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, this->uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(glm::vec2), &indexed_uvs[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, this->normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(glm::vec3), &indexed_normals[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);


    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    glm::mat4 modelMatrix = glm::mat4(1.0);

    glUniformMatrix4fv(this->matID, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(this->modID, 1, GL_FALSE, &modelMatrix[0][0]);


    // Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->m_textures[comp.getTextureID()]);
    // Set our "myTextureSampler" sampler to use Texture Unit 0
    glUniform1i(this->textureID, 0);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
    glVertexAttribPointer(
            0,                  // attribute
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
    );

    // 2nd attribute buffer : UVs
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, this->uvBuffer);
    glVertexAttribPointer(
            1,                                // attribute
            2,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
    );

    // 3rd attribute buffer : normals
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, this->normalBuffer);
    glVertexAttribPointer(
            2,                                // attribute
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
    );

    // Index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->elementBuffer);

    // Draw the triangles !
    glDrawElements(
            GL_TRIANGLES,      // mode
            indices.size(),    // count
            GL_UNSIGNED_SHORT,   // type
            (void*)0           // element array buffer offset
    );

}

void RenderSystem::close() {
    // Cleanup VBO and shader
    glDeleteBuffers(1, &this->vertexBuffer);
    glDeleteBuffers(1, &this->uvBuffer);
    glDeleteBuffers(1, &this->normalBuffer);
    glDeleteBuffers(1, &this->elementBuffer);
    glDeleteProgram(programID);

    for (const GLuint texture : this->m_textures) {
        glDeleteTextures(1, &texture);
    }
}
