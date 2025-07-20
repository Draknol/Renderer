#include <Window.h>
#include <Shader.h>
#include <Texture.h>
#include <LightManager.h>

#include <glm/trigonometric.hpp>

#include <glm/mat4x4.hpp>

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

int main() {

    // Initialise glfw
    glfwInit();

    // Set version to 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    // Create window
    Window window(800, 800);

    // Initialise glew
    glewInit();

    // Disable VSync
    glfwSwapInterval(0);

    // Set clear color
    glClearColor(0.1f, 0.1f, 0.1f, 0.1f);

    // Load and transform models
    Model cube("Cube/Cube.obj", 50);
    cube.scale(glm::vec3(0.2));

    Model floor("Floor/Floor.obj");
    floor.scale(glm::vec3(7, 0.1, 7));
    floor.translate(glm::vec3(0.65, -3, 0.65));

    Model donut("Donut/Donut.obj", 50);
    donut.translate(glm::vec3(0.0f, -0.24f, 0.0f));
    donut.scale(glm::vec3(1.3));

    // Transform instances to create a grid of them
    for (size_t i = 0; i < 50; i++) {
        cube.translate(glm::vec3((2*i) / 10, 0, (2*i) % 10), i);
        donut.translate(glm::vec3((2*i) / 10, 0, (2*i+1) % 10), i);
    }

    // Create shader for making shadowMaps
    Shader depthShader("depthShader.vert", "depthShader.frag");
    window.useProgram(depthShader.getID());

    // Create shader for rendering
    Shader shader("vertexShader.vert", "fragmentShader.frag");
    window.useProgram(shader.getID());

    // Directional lights
    std::vector<DirectionalLight> directionalLights = {
        DirectionalLight(-7.0f, 7.0f, 7.0f, -7.0f, glm::vec3(8.0f, 4.0f, 10.0f), glm::vec3(-0.2f, -0.3f, -0.3f), glm::vec3(0.3f, 0.3f, 0.3f))
    };

    // Point lights
    std::vector<PointLight> pointLights = {
        PointLight(1.0f, 0.35f, 0.44f, glm::vec3(9.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)),
        PointLight(1.0f, 0.35f, 0.44f, glm::vec3(9.0f, 1.0f, 9.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
        PointLight(1.0f, 0.35f, 0.44f, glm::vec3(0.0f, 1.0f, 9.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
        PointLight(1.0f, 0.35f, 0.44f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f)),
    };

    // Spotlights
    std::vector<Spotlight> spotLights = {
        Spotlight(glm::radians(25.0f), 1.0f, 0.09f, 0.032f, glm::vec3(5.0f, 3.0f, 5.0f), glm::vec3(0.1f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)),
        Spotlight(glm::radians(25.0f), 1.0f, 0.09f, 0.032f, glm::vec3(2.0f, 1.0f, 3.0f), glm::vec3(1.0f, -0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)),
        Spotlight(glm::radians(25.0f), 1.0f, 0.09f, 0.032f, glm::vec3(8.0f, 1.0f, 7.0f), glm::vec3(-1.0f, -0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)),
        Spotlight(glm::radians(25.0f), 1.0f, 0.09f, 0.032f, glm::vec3(2.0f, 3.0f, 5.0f), glm::vec3(-0.1f, -0.2f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f))
    };

    LightManager lights(directionalLights, pointLights, spotLights);
    lights.updateUniforms(shader);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // MSAA
    glEnable(GL_MULTISAMPLE);
    
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

        cube.rotate(glm::radians(90.0f * deltaTime), glm::vec3(0.0f, 1.0f, 0.0f));
        donut.rotate(glm::radians(90.0f * deltaTime), glm::vec3(0.0f, 1.0f, 0.0f));

        // Update models
        cube.updateTransforms();
        donut.updateTransforms();
        floor.updateTransforms();

        // Set up shadow map
        window.useProgram(depthShader.getID());

        // Clear shadow buffer
        lights.clear();

        // Render shadows
        lights.draw(cube, depthShader);
        lights.draw(donut, depthShader);
        lights.draw(floor, depthShader);

        // Swap back to window
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, window.getWidth(), window.getHeight());
        glCullFace(GL_BACK);

        // Clear color buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set shader program to use
        window.useProgram(shader.getID());

        window.updateView();

        window.draw(cube, shader);
        window.draw(donut, shader);
        window.draw(floor, shader);

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