//
// Created by notjustin on 12/19/17.
//
#include "CameraController.h"

glm::mat4 CameraController::render() {
    computeMatricesFromInputs();
    glm::mat4 ProjectionMatrix = getProjectionMatrix();
    glm::mat4 ViewMatrix = getViewMatrix();
    glm::mat4 ModelMatrix = glm::mat4(1.0);
    return ProjectionMatrix * ViewMatrix * ModelMatrix;
}

void CameraController::computeMatricesFromInputs() {
    if (!m_window) {
        // TODO create a logging system that opens a console or something
        return;
    }

    double currentTime = glfwGetTime();
    auto deltaTime = float(currentTime - m_dLastTime);
    m_dLastTime = currentTime;

    // Get mouse pos
    double xpos, ypos;
    glfwGetCursorPos(m_window, &xpos, &ypos);
    // Reset mouse pos for next frame
    glfwSetCursorPos(m_window, 1280 / 2, 720 / 2);

    // Compute new orientation
    m_fhAngle += m_fMouseSpeed * deltaTime * float(1280 / 2 - xpos);
    m_fvAngle += m_fMouseSpeed * deltaTime * float(720 / 2 - ypos);

    // Direction : Spherical coordinates to Cartesian coordinates conversion
    glm::vec3 direction(
            glm::cos(m_fvAngle) * glm::sin(m_fhAngle),
            glm::sin(m_fvAngle),
            glm::cos(m_fvAngle) * glm::cos(m_fhAngle)
    );

    // Right vector
    glm::vec3 right = glm::vec3(
            glm::sin(m_fhAngle - 3.14f / 2.0f),
            0,
            glm::cos(m_fhAngle - 3.14f / 2.0f)
    );

    // Up vector : perpendicular to both direction and right
    glm::vec3 up = glm::cross(right, direction);

    // Move forward
    if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS) {
        m_pos += direction * deltaTime * m_fSpeed;
    }
    // Move backward
    if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS) {
        m_pos -= direction * deltaTime * m_fSpeed;
    }
    // Strafe right
    if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS) {
        m_pos += right * deltaTime * m_fSpeed;
    }
    // Strafe left
    if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS) {
        m_pos -= right * deltaTime * m_fSpeed;
    }
    // go up
    if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        m_pos += up * deltaTime * m_fSpeed;
    }
    // go down
    if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        m_pos -= up * deltaTime * m_fSpeed;
    }

    m_projMat = glm::perspective(glm::radians(m_fFov), 16.0f / 9.0f, 0.1f, 100.0f);
    m_viewMat = glm::lookAt(
            m_pos,           // Camera is here
            m_pos + direction, // and looks here : at the same pos, plus "direction"
            up                  // Head is up (set to 0,-1,0 to look upside-down)
    );
}

glm::mat4 CameraController::getProjectionMatrix() {
    return m_projMat;
}

glm::mat4 CameraController::getViewMatrix() {
    return m_viewMat;
}