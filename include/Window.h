#ifndef WINDOW_H
#define WINDOW_H

#include <Model.h>
#include <View.h>

#include <GLFW/glfw3.h>

/// @brief Container for OpenGL's GLFWwindow
class Window
{
private:
    GLFWwindow* window;

    GLint currentProgram;
    GLsizei width, height;

    glm::vec2 lastMousePosition;
public:
    View view;

    /// @brief Create and initialise a window
    Window(GLsizei width, GLsizei height);
    ~Window();

    /// @brief Draw a Model to screen (call update to display frame)
    /// @param model Model to draw
    void draw(Model& model, Shader& shader);

    /// @brief Process inputs
    void processInput(float deltaTime);

    /// @brief Change which shader program is in use
    /// @param ID Program ID
    void useProgram(GLuint ID);

    /// @brief Checks if the window should be closed
    /// @return true if the window should close
    int shouldClose() { return glfwWindowShouldClose(window); }

    /// @brief Display the current frame
    void update();

    void updateView();

    GLsizei getWidth() const { return width; }
    GLsizei getHeight() const { return height; }

protected:

    /// @brief Callback for resizing the window and updating the view
    static void windowResized(GLFWwindow* window, GLsizei width, GLsizei height);

    /// @brief Callback for moving the mouse to update the view
    static void mouseMoved(GLFWwindow* window, double xpos, double ypos);

    /// @brief Callback for scrolling the scroll wheel to update camera speed
    static void scrolled(GLFWwindow* window, double xoffset, double yoffset);
};

#endif