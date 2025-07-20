#include <DirectionalLight.h>

DirectionalLight::DirectionalLight(float left, float right, float bottom, float top, const glm::vec3& position, const glm::vec3& direction, const glm::vec3& color)
    : BasicLight(glm::ortho(left, right, bottom, top, 0.1f, 100.0f), position, direction, color) {}