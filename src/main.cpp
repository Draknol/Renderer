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
    glClearColor(0.1f, 0.1f, 0.1f, 0.1f);

    // Load Model
    Model cube("Cube/Cube.obj", 50);
    cube.scale(glm::vec3(0.2));

    Model donut("Donut/Donut.obj", 50);
    donut.translate(glm::vec3(0.0f, -0.2f, 0.0f));
    donut.scale(glm::vec3(0.7));

    for (size_t i = 0; i < 50; i++) {
        cube.translate(glm::vec3((2*i) / 10, 0, (2*i) % 10), i);
        donut.translate(glm::vec3((2*i+1) / 10, 0, (2*i+1) % 10), i);
    }
    
    // Create Shader
    Shader shader("vertexShader.vert", "fragmentShader.frag");
    window.useProgram(shader.getID());

    // Directional
    shader.setVec3("directionalLight.direction", glm::vec3(-0.2f, -0.3f, -0.3f));
    shader.setVec3("directionalLight.color", glm::vec3(0.3f, 0.3f, 0.3f)); 

    // Point
    shader.setVec3("pointLights[0].position", glm::vec3(10.0f, 1.0f, 0.0f));
    shader.setVec3("pointLights[0].color", glm::vec3(1.0f, 0.0f, 0.0f));
    shader.setFloat("pointLights[0].constant", 1.0f);
    shader.setFloat("pointLights[0].linear", 0.35f);
    shader.setFloat("pointLights[0].quadratic", 0.44f);

    shader.setVec3("pointLights[1].position", glm::vec3(10.0f, 1.0f, 10.0f));
    shader.setVec3("pointLights[1].color", glm::vec3(0.0f, 1.0f, 0.0f)); 
    shader.setFloat("pointLights[1].constant", 1.0f);
    shader.setFloat("pointLights[1].linear", 0.35f);
    shader.setFloat("pointLights[1].quadratic", 0.44f);

    shader.setVec3("pointLights[2].position", glm::vec3(0.0f, 1.0f, 10.0f));
    shader.setVec3("pointLights[2].color", glm::vec3(0.0f, 0.0f, 1.0f)); 
    shader.setFloat("pointLights[2].constant", 1.0f);
    shader.setFloat("pointLights[2].linear", 0.35f);
    shader.setFloat("pointLights[2].quadratic", 0.44f);

    shader.setVec3("pointLights[3].position", glm::vec3(0.0f, 1.0f, 0.0f));
    shader.setVec3("pointLights[3].color", glm::vec3(1.0f, 0.0f, 1.0f)); 
    shader.setFloat("pointLights[3].constant", 1.0f);
    shader.setFloat("pointLights[3].linear", 0.35f);
    shader.setFloat("pointLights[3].quadratic", 0.44f);

    // Spotlight
    shader.setVec3("spotlights[0].position",  glm::vec3(5.0f, 3.0f, 5.0f));
    shader.setVec3("spotlights[0].direction", glm::vec3(0.0f, -0.2f, 0.0f));
    shader.setVec3("spotlights[0].color", glm::vec3(1.0f, 1.0f, 1.0f));  
    shader.setFloat("spotlights[0].cutOff",   glm::cos(glm::radians(12.5f)));
    shader.setFloat("spotlights[0].constant", 1.0f);
    shader.setFloat("spotlights[0].linear", 0.09f);
    shader.setFloat("spotlights[0].quadratic", 0.032f);

    shader.setVec3("spotlights[1].position",  glm::vec3(2.0f, 0.2f, 3.0f));
    shader.setVec3("spotlights[1].direction", glm::vec3(1.0f, 0.1f, 0.0f));
    shader.setVec3("spotlights[1].color", glm::vec3(1.0f, 1.0f, 1.0f));   
    shader.setFloat("spotlights[1].cutOff",   glm::cos(glm::radians(12.5f)));
    shader.setFloat("spotlights[1].constant", 1.0f);
    shader.setFloat("spotlights[1].linear", 0.09f);
    shader.setFloat("spotlights[1].quadratic", 0.032f);

    shader.setVec3("spotlights[2].position",  glm::vec3(8.0f, 0.2f, 7.0f));
    shader.setVec3("spotlights[2].direction", glm::vec3(-1.0f, -0.1f, 0.0f));
    shader.setVec3("spotlights[2].color", glm::vec3(1.0f, 1.0f, 1.0f)); 
    shader.setFloat("spotlights[2].cutOff",   glm::cos(glm::radians(12.5f)));
    shader.setFloat("spotlights[2].constant", 1.0f);
    shader.setFloat("spotlights[2].linear", 0.09f);
    shader.setFloat("spotlights[2].quadratic", 0.032f);

    shader.setVec3("spotlights[3].position",  glm::vec3(2.0f, 3.0f, 5.0f));
    shader.setVec3("spotlights[3].direction", glm::vec3(0.0f, -0.2f, 0.0f));
    shader.setVec3("spotlights[3].color", glm::vec3(1.0f, 1.0f, 1.0f));
    shader.setFloat("spotlights[3].cutOff",   glm::cos(glm::radians(12.5f)));
    shader.setFloat("spotlights[3].constant", 1.0f);
    shader.setFloat("spotlights[3].linear", 0.09f);
    shader.setFloat("spotlights[3].quadratic", 0.032f);

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
        
        cube.rotate(glm::radians(90.0f * deltaTime), glm::vec3(0.0f, 1.0f, 0.0f));
        donut.rotate(glm::radians(90.0f * deltaTime), glm::vec3(0.0f, 1.0f, 0.0f));

        window.draw(cube, shader);
        window.draw(donut, shader);

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