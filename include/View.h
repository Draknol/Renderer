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
public:

    /// @brief Create a view
    /// @param width Width of the window
    /// @param height Height of the window
    View(float width, float height);

    /// @brief Update the view to match new window size (only call when window changes size)
    /// @param width Width of the window
    /// @param height Height of the window
    void update(float width, float height);

    const glm::mat4& getProjView() { return projView; }
};

#endif