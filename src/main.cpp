#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/trigonometric.hpp>

#include <VertexArray.h>
#include <Shader.h>
#include <Texture.h>

#include <iostream>

const GLsizei SCREEN_WIDTH = 800;
const GLsizei SCREEN_HEIGHT = 800;

Vertex vertices[] = {
//      x      y      z       rgba      s     t
    { -0.5f, -0.5f,  0.5f, 0xFFFFFFFF, 0.0f, 0.0f },
    {  0.5f, -0.5f,  0.5f, 0xFFFFFFFF, 1.0f, 0.0f },
    {  0.5f,  0.5f,  0.5f, 0xFFFFFFFF, 1.0f, 1.0f },
    { -0.5f,  0.5f,  0.5f, 0xFFFFFFFF, 0.0f, 1.0f },

    {  0.5f, -0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 0.0f },
    { -0.5f, -0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 0.0f },
    { -0.5f,  0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f },
    {  0.5f,  0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f },

    { -0.5f, -0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 0.0f },
    { -0.5f, -0.5f,  0.5f, 0xFFFFFFFF, 1.0f, 0.0f },
    { -0.5f,  0.5f,  0.5f, 0xFFFFFFFF, 1.0f, 1.0f },
    { -0.5f,  0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f },

    {  0.5f, -0.5f,  0.5f, 0xFFFFFFFF, 0.0f, 0.0f },
    {  0.5f, -0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 0.0f },
    {  0.5f,  0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f },
    {  0.5f,  0.5f,  0.5f, 0xFFFFFFFF, 0.0f, 1.0f },

    { -0.5f,  0.5f,  0.5f, 0xFFFFFFFF, 0.0f, 0.0f },
    {  0.5f,  0.5f,  0.5f, 0xFFFFFFFF, 1.0f, 0.0f },
    {  0.5f,  0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f },
    { -0.5f,  0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f },

    { -0.5f, -0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 0.0f },
    {  0.5f, -0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 0.0f },
    {  0.5f, -0.5f,  0.5f, 0xFFFFFFFF, 1.0f, 1.0f },
    { -0.5f, -0.5f,  0.5f, 0xFFFFFFFF, 0.0f, 1.0f },
};

GLuint indices[] = {
     0,  1,  2,  0,  2,  3,
     4,  5,  6,  4,  6,  7,
     8,  9, 10,  8, 10, 11,
    12, 13, 14, 12, 14, 15,
    16, 17, 18, 18, 19, 16,
    20, 21, 22, 22, 23, 20,
};

void processInput(GLFWwindow *window);  

// Callbacks
void windowResized(GLFWwindow* window, GLsizei width, GLsizei height);

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
        std::cout << "ERROR::WINDOW::CREATION_FAILED\n";
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

    // Create VertexArray
    VertexArray vertexArray(vertices, sizeof(vertices), indices, sizeof(indices));

    // Create Shader
    Shader shader("vertexShader.vert", "fragmentShader.frag");
    shader.useProgram();

    // Load texture
    Texture texture("wall.jpg"); // Texture is from learnopengl.com

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    

    GLfloat lastFrame = glfwGetTime();
    GLfloat frameTime = 0;
    GLint FPS = 0;

    // Main loop
    while (!glfwWindowShouldClose(window)) {

        GLfloat currentFrame = glfwGetTime();
        GLfloat deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Input
        processInput(window);

        // Clear color buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set shader program to use
        shader.useProgram();

        glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f  ), 
            glm::vec3( 2.0f,  5.0f, -15.0f ), 
            glm::vec3(-1.5f, -2.2f, -2.5f  ),  
            glm::vec3(-3.8f, -2.0f, -12.3f ),  
            glm::vec3( 2.4f, -0.4f, -3.5f  ),  
            glm::vec3(-1.7f,  3.0f, -7.5f  ),  
            glm::vec3( 1.3f, -2.0f, -2.5f  ),  
            glm::vec3( 1.5f,  2.0f, -2.5f  ), 
            glm::vec3( 1.5f,  0.2f, -1.5f  ), 
            glm::vec3(-1.3f,  1.0f, -1.5f  ),
        };
        
        for (size_t j = 0; j < 10 / 10; j++)
        {
            for(unsigned int i = 0; i < 10; i++) {
            float angle = (90.0f * currentFrame) + (20.0f * i);

            vertexArray.resetTransform();
            vertexArray.translate(cubePositions[i]);
            vertexArray.rotate(glm::radians(angle), glm::vec3(1.0f, 0.5f, 0.5f));

            vertexArray.draw(window);
        }
        }

        // Update window
        glfwSwapBuffers(window);

        frameTime += deltaTime;
        FPS++;
        if (frameTime >= 1) {
            std::cout << "FPS: " << FPS << std::endl;
            frameTime = 0;
            FPS = 0;
        }

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

void windowResized(GLFWwindow* window, GLsizei width, GLsizei height) {
    // Recreate viewport
    glViewport(0, 0, width, height);
}