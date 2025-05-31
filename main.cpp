#include <iostream>

#include <windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

const char* vertexShaderSource = (
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0"
);

const char* fragmentShaderSource = (
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0"
);

void processInput(GLFWwindow *window);

// Simple 2D geometry (square with a hole)
float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    -0.25f, -0.25f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.25f, -0.25f, 0.0f,
    0.5f, 0.5f, 0.0f,
    0.25f, 0.25f, 0.0f,
    -0.5f, 0.5f, 0.0f,
    -0.25f, 0.25f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.25f, -0.25f, 0.0f
};

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

    // Create shaders
    GLuint vertexShader;
    GLuint fragmentShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Compile shaders
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    // Create shader program
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();

    // Attach shaders to program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Delete linked shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Create and bind VAO
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    // Copy array to buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Apply attributes to VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // Main loop
    while (!glfwWindowShouldClose(window)) {

        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        
        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, sizeof(vertices) / sizeof(float));

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