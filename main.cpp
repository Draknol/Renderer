#include <iostream>

#include <windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

void processInput(GLFWwindow *window);

// Callbacks
void windowResized(GLFWwindow* window, int width, int height);

int main() {

    // Initialise glfw
    glfwInit();

    // Set version to 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Renderer", NULL, NULL);

    // Check window was created
    if (!window) {
        std::cout << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }

    // Set window as main window
    glfwMakeContextCurrent(window);

    // Disable VSync
    glfwSwapInterval(0);

    // Create a viewport
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Set function to be called on size change
    glfwSetFramebufferSizeCallback(window, windowResized);

    // Set clear color
    glClearColor(0.5f, 0.65f, 0.85f, 1.0f);
    
    // Main loop
    while (!glfwWindowShouldClose(window)) {

        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    // Exit
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window) {
    // Escape
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void windowResized(GLFWwindow* window, int width, int height) {
    // Recreate viewport
    glViewport(0, 0, width, height);
}