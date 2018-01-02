#include <GL/glew.h>
#include "PrimitiveRenderer.h"

using namespace VapeRenderer;

PrimitiveRenderer::PrimitiveRenderer(Core::GameObject *_parent, PrimitiveShapes _shape) :
        ObjectRenderer(_parent), m_shape(_shape)  {
    //Constructor
}

void PrimitiveRenderer::render() {
    switch(m_shape) {
        case CUBE:
            renderCube();
            break;
        case PLANE:
            renderPlane();
            break;
        case PYRAMID:
            break;
        case OCTOHEDRAL:
            break;
        case CYLINDER:
            break;
        case SPHERE:
            break;
    }
}

void PrimitiveRenderer::renderCube() {
    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_color_buffer_data), cube_color_buffer_data, GL_STATIC_DRAW);

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

    GLuint vertex_buf; // identify the vertex buffer
    glGenBuffers(1, &vertex_buf); // generate 1 buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertex_buffer_data), cube_vertex_buffer_data, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buf);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glDrawArrays(GL_TRIANGLES, 0, 12*3);
    glDisableVertexAttribArray(0);
}

void PrimitiveRenderer::renderPlane() {
    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(plane_color_buffer_data), plane_color_buffer_data, GL_STATIC_DRAW);

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

    GLuint vertex_buf; // identify the vertex buffer
    glGenBuffers(1, &vertex_buf); // generate 1 buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(plane_vertex_buffer_data), plane_vertex_buffer_data, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buf);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glDrawArrays(GL_TRIANGLES, 0, 6*3);
    glDisableVertexAttribArray(0);
}
