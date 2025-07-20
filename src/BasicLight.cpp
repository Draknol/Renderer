#include <BasicLight.h>

BasicLight::BasicLight(const glm::mat4& projection, const glm::vec3& position, const glm::vec3& direction, const glm::vec3& color)
    : projection(projection), position(position), direction(direction), color(color) {
    // Create projection and view
    view = glm::lookAt(position, position + direction, glm::vec3(0.0f, 1.0f, 0.0f));
    projView = projection * view;

    // Create depthMapFBO
    glGenFramebuffers(1, &depthMapFBO);
}

BasicLight& BasicLight::operator=(const BasicLight& other) {
    if (this == &other) return *this;

    // Copy to avoid making a new FPO
    depthMapFBO = other.depthMapFBO;
    projView = other.projView;
    projection = other.projection;
    view = other.view;

    position = other.position;
    direction = other.direction;
    color = other.color;

    return *this;
}