#include <PointLight.h>

PointLight::PointLight(float constant, float linear, float quadratic, const glm::vec3& position, const glm::vec3& color)
    : BasicLight(glm::mat4(1.0), position, glm::vec3(1.0), color), constant(constant), linear(linear), quadratic(quadratic) {}