#include <render/util/texture.h>
#include <render/util/objloader.h>
#include "ModelRenderer.h"

VapeRenderer::ModelRenderer::ModelRenderer(Core::GameObject *_parent) : ObjectRenderer(_parent) {

}

VapeRenderer::ModelRenderer::ModelRenderer(Core::GameObject *_parent, char* _modelPath, char* _texturePath) :
        ObjectRenderer(_parent), m_modelPath(_modelPath), m_texturePath(_texturePath) {

}

void VapeRenderer::ModelRenderer::init(GLuint *_programID, GLuint *_textureID) {
    this->m_texture = loadDDS(m_texturePath);
    bool res = loadOBJ(m_modelPath, this->m_vertices, this->m_uvs, this->m_normals);

    this->m_programID = _programID;
    this->m_textureID = _textureID;

    this->b_init = true;
}

void VapeRenderer::ModelRenderer::render(GLuint *vertex_buf) {
    ObjectRenderer::render(vertex_buf);
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, this->m_vertices.size() * sizeof(glm::vec3), &this->m_vertices[0], GL_STATIC_DRAW);

    GLuint uvbuffer;
    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, this->m_uvs.size() * sizeof(glm::vec2), &this->m_uvs[0], GL_STATIC_DRAW);

    // Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->m_texture);
    // Set our "myTextureSampler" sampler to use Texture Unit 0
    glUniform1i(*this->m_textureID, 0);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
            0,                  // attribute
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            nullptr            // array buffer offset
    );

    // 2nd attribute buffer : UVs
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glVertexAttribPointer(
            1,                                // attribute
            2,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            nullptr                          // array buffer offset
    );

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, this->m_vertices.size());

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
