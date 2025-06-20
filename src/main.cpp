#include <Window.h>
#include <Shader.h>
#include <Texture.h>

#include <glm/trigonometric.hpp>

#include <iostream>

const GLsizei SCREEN_WIDTH = 800;
const GLsizei SCREEN_HEIGHT = 800;

int main() {

    // Initialise glfw
    glfwInit();

    // Set version to 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Window window(SCREEN_WIDTH, SCREEN_HEIGHT);

    glewInit();

    // Disable VSync
    glfwSwapInterval(0);

    // Set clear color
    glClearColor(0.5f, 0.65f, 0.85f, 1.0f);

    // Load Model
    Model model("Donut/Donut.obj");

    // Create Shader
    Shader shader("vertexShader.vert", "fragmentShader.frag");
    window.useProgram(shader.getID());


    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    // FPS
    GLfloat lastFrame = glfwGetTime();
    GLfloat frameTime = 0;
    GLint FPS = 0;

    // Main loop
    while (!window.shouldClose()) {

        GLfloat currentFrame = glfwGetTime();
        GLfloat deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        window.processInput(deltaTime);

        // Clear color buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set shader program to use
        window.useProgram(shader.getID());

        window.updateView();

        window.draw(model, shader);

        window.update();

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