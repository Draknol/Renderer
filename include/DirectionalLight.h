#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include <BasicLight.h>

/// @brief A light with an orthographic shadow map
class DirectionalLight : public BasicLight {
public:
    /// @brief Constructor for a DirectionalLight
    /// @param left Left of the view
    /// @param right Right of the view
    /// @param bottom Bottom of the view
    /// @param top Top of the view
    /// @param position Position of the light (only affects what is in view)
    /// @param direction Direction light is shining
    /// @param color Color of the light
    DirectionalLight(float left, float right, float bottom, float top, const glm::vec3& position, const glm::vec3& direction, const glm::vec3& color);
};

#endif