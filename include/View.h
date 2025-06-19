#ifndef VIEW_H
#define VIEW_H

#include <glm/mat4x4.hpp>

/// @brief Acts as a camera, with a view, aspect ratio and projection
class View
{
private:
    float aspectRatio;
    glm::mat4 projection;
    glm::mat4 view;
    glm::mat4 projView;

    float yaw = -90.0f;
    float pitch = 0.0f;
    
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 5.0f);
    glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f);
    constexpr static glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    float cameraSpeed = 15.0f;
    float fov = 90.0f;
public:

    /// @brief Create a view
    /// @param width Width of the window
    /// @param height Height of the window
    View(float width, float height);

    /// @brief Update the view to match new window size (only call when window changes size)
    /// @param width Width of the window
    /// @param height Height of the window
    void updateViewPort(float width, float height);

    void update();

    void move(float cameraSpeed, int direction);

    void rotate(float yawOffset, float pitchOffset);

    const glm::mat4& getProjView() { return projView; }
};

#endif