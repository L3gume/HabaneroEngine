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
    if (!window) {
        // TODO create a logging system that opens a console or something
        return;
    }

    double currentTime = glfwGetTime();
    auto deltaTime = float(currentTime - last_time);
    last_time = currentTime;

    // Get mouse pos
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    // Reset mouse pos for next frame
    glfwSetCursorPos(window, 1280 / 2, 720 / 2);

    // Compute new orientation
    h_angle += mouse_speed * deltaTime * float(1280 / 2 - xpos);
    v_angle += mouse_speed * deltaTime * float(720 / 2 - ypos);

    // Direction : Spherical coordinates to Cartesian coordinates conversion
    glm::vec3 direction(
            glm::cos(v_angle) * glm::sin(h_angle),
            glm::sin(v_angle),
            glm::cos(v_angle) * glm::cos(h_angle)
    );

    // Right vector
    glm::vec3 right = glm::vec3(
            glm::sin(h_angle - 3.14f / 2.0f),
            0,
            glm::cos(h_angle - 3.14f / 2.0f)
    );

    // Up vector : perpendicular to both direction and right
    glm::vec3 up = glm::cross(right, direction);

    // Move forward
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        pos += direction * deltaTime * speed;
    }
    // Move backward
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        pos -= direction * deltaTime * speed;
    }
    // Strafe right
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        pos += right * deltaTime * speed;
    }
    // Strafe left
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        pos -= right * deltaTime * speed;
    }
    // go up
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        pos += up * deltaTime * speed;
    }
    // go down
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        pos -= up * deltaTime * speed;
    }

    projMat = glm::perspective(glm::radians(fov), 16.0f / 9.0f, 0.1f, 100.0f);
    viewMat = glm::lookAt(
            pos,           // Camera is here
            pos + direction, // and looks here : at the same pos, plus "direction"
            up                  // Head is up (set to 0,-1,0 to look upside-down)
    );
}

glm::mat4 CameraController::getProjectionMatrix() {
    return projMat;
}

glm::mat4 CameraController::getViewMatrix() {
    return viewMat;
}