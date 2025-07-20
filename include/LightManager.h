#ifndef LIGHT_MANAGER_H
#define LIGHT_MANAGER_H

#include <DirectionalLight.h>
#include <Spotlight.h>
#include <PointLight.h>
#include <Shader.h>
#include <Model.h>

#include <vector>

/// @brief Manages multiple of each light type
class LightManager
{
private:

    std::vector<DirectionalLight> directionals;
    std::vector<PointLight> points;
    std::vector<Spotlight> spots;
    
    // Color for outside the shadow map
    static constexpr float borderColor[] = {1.0f, 1.0f, 1.0f, 1.0f};

    GLuint directionalShadowMaps;
    GLuint spotShadowMaps;
    
public:

    // Textures sizes for the shadows
    static const GLuint DIRECTIONAL_SHADOW_SIZE = 4096;
    static const GLuint SPOT_SHADOW_SIZE = 512;

    /// @brief Constructor for a LightManager
    LightManager(const std::vector<DirectionalLight>& directionals, const std::vector<PointLight>& points, const std::vector<Spotlight>& spots);

    /// @brief Draws a model to a depth map
    /// @param model Model to draw
    /// @param shader Shader to use
    void draw(Model& model, Shader& shader);

    /// @brief Sets all the uniforms needed for rendering shadows
    /// Only needs calling after construction or after lights are changed
    /// @param shader Shader to update uniforms of
    void updateUniforms(Shader& shader);

    /// @brief Clear every lights FBO
    void clear();
};

#endif