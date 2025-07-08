#include <View.h>

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <algorithm>

View::View(float width, float height) {
    update();
    updateViewPort(width, height);
}

void View::updateViewPort(float width, float height) {
    aspectRatio = width / height;
    glViewport(0, 0, width, height);
    projection = glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 100.0f);
    projView = projection * view;
}

void View::update() {
    forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    forward.y = sin(glm::radians(pitch));
    forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    view = glm::lookAt(position, position + forward, up);
    projView = projection * view;
}

void View::move(float deltaTime, int direction) {
    switch (direction) {
    case 1:
        position += deltaTime * cameraSpeed * forward;
        break;
    case 2:
        position -= deltaTime * cameraSpeed * forward;
        break;
    case 3:
        position -= glm::normalize(glm::cross(forward, up)) * deltaTime * cameraSpeed;
        break;
    case 4:
        position += glm::normalize(glm::cross(forward, up)) * deltaTime * cameraSpeed;
        break;
    default:
        break;
    }
}

void View::rotate(float yawOffset, float pitchOffset) {
    yaw += yawOffset;
    pitch += pitchOffset;

    pitch = std::clamp(pitch, -89.0f, 89.0f);
}

void View::multiplySpeed(float multiple) {
    cameraSpeed = std::clamp(cameraSpeed * multiple, minSpeed, maxSpeed);
}