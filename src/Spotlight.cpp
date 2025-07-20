#include <Spotlight.h>

#include <glm/glm.hpp>
#include <glm/trigonometric.hpp>

Spotlight::Spotlight(float fov, float constant, float linear, float quadratic, const glm::vec3& position, const glm::vec3& direction, const glm::vec3& color)
    : BasicLight(glm::perspective(fov, 1.0f, 0.1f, 100.0f), position, direction, color), cutOff(glm::cos(fov / 2.0f)), constant(constant), linear(linear), quadratic(quadratic) {}