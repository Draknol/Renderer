#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include <BasicLight.h>

/// @brief A light without a direction (currently has no shadows)
class PointLight : public BasicLight {
private:

    // Light fall off
    float constant;
    float linear;
    float quadratic;

public:

    /// @brief Constructor for a PointLight
    /// @param constant Constant term of light fall off
    /// @param linear Linear term of light fall off
    /// @param quadratic Quadratic term of light fall off
    /// @param position Postion of the light
    /// @param color Color of the light
    PointLight(float constant, float linear, float quadratic, const glm::vec3& position, const glm::vec3& color);
    
    float getConstant() const { return constant; }
    float getLinear() const { return linear; }
    float getQuadratic() const { return quadratic; }

};

#endif