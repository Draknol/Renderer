#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include <BasicLight.h>

/// @brief A light with a perspective shadow map
class Spotlight : public BasicLight {
private:

    // Light fall off
    float constant;
    float linear;
    float quadratic;

    // Cut off angle
    float cutOff;

public:

    /// @brief Constructor for a Spotlight
    /// @param fov FOV of the perspective, affects how wide the light is
    /// @param constant Constant term of light fall off
    /// @param linear Linear term of light fall off
    /// @param quadratic Quadratic term of light fall off
    /// @param position Postion of the light
    /// @param direction Direction the light is shining
    /// @param color Color of the light
    Spotlight(float fov, float constant, float linear, float quadratic, const glm::vec3& position, const glm::vec3& direction, const glm::vec3& color);

    float getConstant() const { return constant; }
    float getLinear() const { return linear; }
    float getQuadratic() const { return quadratic; }
    float getCutOff() const { return cutOff; }

};

#endif