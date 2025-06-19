#ifndef WINDOW_H
#define WINDOW_H

#include <VertexArray.h>
#include <View.h>

/// @brief Container for OpenGL's GLFWwindow
class Window
{
private:
    GLFWwindow* window;
    View view;

    GLint currentProgram;
    GLint transformLocation;
    GLsizei width, height;
public:

    /// @brief Create and initialise a window
    Window(GLsizei width, GLsizei height);
    ~Window();

    /// @brief Draw a VertexArray to screen (call update to display frame)
    /// @param vertexArray VertexArray to draw
    void draw(VertexArray& vertexArray);

    /// @brief Process inputs
    void processInput();

    /// @brief Change which shader program is in use
    /// @param ID Program ID
    void useProgram(GLuint ID);

    /// @brief Checks if the window should be closed
    /// @return true if the window should close
    int shouldClose() { return glfwWindowShouldClose(window); }

    /// @brief Display the current frame
    void update();

protected:

    /// @brief Callback for resizing the window and updating the view
    static void windowResized(GLFWwindow* window, GLsizei width, GLsizei height);
};

#endif