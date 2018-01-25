#include <GL/glew.h>
#include <glm/glm.hpp>
#include "PrimitiveRenderer.h"

using namespace VapeRenderer;

PrimitiveRenderer::PrimitiveRenderer(Core::GameObject *_parent, PrimitiveShapes _shape) :
        ObjectRenderer(_parent), m_shape(_shape) {
    //Constructor
}

void PrimitiveRenderer::render(GLuint* vertex_buf) {
    switch(m_shape) {
        case CUBE:
            renderCube(vertex_buf);
            break;
        case PLANE:
            renderPlane(vertex_buf);
            break;
        case PYRAMID:
            renderPyramid(vertex_buf);
            break;
        case OCTAHEDRON:
            renderOctahedron(vertex_buf);
            break;
        case CYLINDER:
            renderCylinder(vertex_buf);
            break;
        case SPHERE:
            renderSphere(vertex_buf);
            break;
    }
}

void PrimitiveRenderer::renderCube(GLuint* vertex_buf) {
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

    glBindBuffer(GL_ARRAY_BUFFER, *vertex_buf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertex_buffer_data), cube_vertex_buffer_data, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, *vertex_buf);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glDrawArrays(GL_TRIANGLES, 0, 12*3);
}

void PrimitiveRenderer::renderPlane(GLuint* vertex_buf) {
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

    glBindBuffer(GL_ARRAY_BUFFER, *vertex_buf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(plane_vertex_buffer_data), plane_vertex_buffer_data, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, *vertex_buf);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glDrawArrays(GL_TRIANGLES, 0, 6*3);
}

void PrimitiveRenderer::renderPyramid(GLuint *vertex_buf) {
    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pyramid_color_buffer_data), pyramid_color_buffer_data, GL_STATIC_DRAW);

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

    glBindBuffer(GL_ARRAY_BUFFER, *vertex_buf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pyramid_vertex_buffer_data), pyramid_vertex_buffer_data, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, *vertex_buf);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glDrawArrays(GL_TRIANGLES, 0, 12*3);
}

void PrimitiveRenderer::renderOctahedron(GLuint *vertex_buf) {

}

void PrimitiveRenderer::renderCylinder(GLuint *vertex_buf) {

}

void PrimitiveRenderer::renderSphere(GLuint *vertex_buf) {
    std::vector<GLfloat> sphereVertices;

    for(int i = 0; i <= 40; i++)
    {
        double lat0 = M_PI * (-0.5 + (double) (i - 1) / 40);
        double z0  = sin(lat0);
        double zr0 =  cos(lat0);

        double lat1 = M_PI * (-0.5 + (double) i / 40);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);

        for(int j = 0; j <= 40; j++)
        {
            double lng = 2 * M_PI * (double) (j - 1) / 40;
            double x = cos(lng);
            double y = sin(lng);

            sphereVertices.push_back(x * zr0); //X
            sphereVertices.push_back(y * zr0); //Y
            sphereVertices.push_back(z0);      //Z

            sphereVertices.push_back(0.0f);
            sphereVertices.push_back(1.0f);
            sphereVertices.push_back(0.0f);
            sphereVertices.push_back(1.0f); //R,G,B,A

            sphereVertices.push_back(x * zr1); //X
            sphereVertices.push_back(y * zr1); //Y
            sphereVertices.push_back(z1);      //Z

            sphereVertices.push_back(0.0f);
            sphereVertices.push_back(1.0f);
            sphereVertices.push_back(0.0f);
            sphereVertices.push_back(1.0f); //R,G,B,A
        }
    }

    glBindBuffer(GL_VERTEX_ARRAY, *vertex_buf);

    GLuint sphereSize = 3200*7*4; //3200 vertices * 7 floats
    glBufferData(GL_VERTEX_ARRAY, sphereSize, &sphereVertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_VERTEX_ARRAY, *vertex_buf);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 7*4, nullptr);
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(4, GL_FLOAT, 7*4, (void*)(3*4));

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 3200);
}
