#ifndef LIGHT_VIEW_H
#define LIGHT_VIEW_H

#include <glm/mat4x4.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

/// @brief A basic light base that creates an FBO
class BasicLight {
protected:

    GLuint depthMapFBO;

    glm::mat4 projView;
    glm::mat4 projection;
    glm::mat4 view;
    
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 color;

    static constexpr glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.5f);

public:

    /// @brief Constructor for a BasicLight
    /// @param projection Projection to be used for shadows
    /// @param position Position of the light
    /// @param direction Direction light is shining
    /// @param color Color of the light
    BasicLight(const glm::mat4& projection, const glm::vec3& position, const glm::vec3& direction, const glm::vec3& color);
    BasicLight& operator=(const BasicLight& other);

    const GLuint getDepthMapFBO() const { return depthMapFBO; }

    const glm::mat4& getProjView() const { return projView; }
    const glm::mat4& getProjection() const { return projection; }
    const glm::mat4& getView() const { return view; }

    const glm::vec3& getPosition() const { return position; }
    const glm::vec3& getDirection() const { return direction; }
    const glm::vec3& getColor() const { return color; }
    
};

#endif