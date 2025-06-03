#include <iostream>
#include <windows.h>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

#include <Shader.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

float vertices[] = {
//    x       y      z      r     g     b    
    -0.5f,  -0.5f,  0.0f,  0.2f, 0.7f, 0.1f,
    -0.25f, -0.25f, 0.0f,  0.9f, 0.3f, 0.4f,
     0.5f,  -0.5f,  0.0f,  0.1f, 0.5f, 0.9f,
     0.25f, -0.25f, 0.0f,  0.6f, 0.4f, 0.9f,
     0.5f,   0.5f,  0.0f,  0.3f, 0.2f, 0.8f,
     0.25f,  0.25f, 0.0f,  0.0f, 0.9f, 0.6f,
    -0.5f,   0.5f,  0.0f,  0.8f, 0.1f, 0.7f,
    -0.25f,  0.25f, 0.0f,  0.5f, 0.0f, 0.3f,
    -0.5f,  -0.5f,  0.0f,  0.2f, 0.7f, 0.1f,
    -0.25f, -0.25f, 0.0f,  0.9f, 0.3f, 0.4f
};

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
    glewInit();

    // Disable VSync
    glfwSwapInterval(0);

    // Create a viewport
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Set function to be called on size change
    glfwSetFramebufferSizeCallback(window, windowResized);

    // Set clear color
    glClearColor(0.5f, 0.65f, 0.85f, 1.0f);

    // Create and bind VBO
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    Shader shader("vertexShader.vert", "fragmentShader.frag");
 
    // Create and bind VAO
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    // Copy array to buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Apply position attribute to VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Apply color attribute to VBO
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // Main loop
    while (!glfwWindowShouldClose(window)) {

        // Input
        processInput(window);

        // Clear color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // Set shader program to use
        shader.useProgram();
        
        // Bind and draw VAO
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, sizeof(vertices) / sizeof(float));

        // Update window
        glfwSwapBuffers(window);

        // Events
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