#include <Window.h>

#include <GL/glew.h>
#include <iostream>

Window::Window(GLsizei width, GLsizei height)
: width(width), height(height), view(width, height) {

    // Create window
    window = glfwCreateWindow(width, height, "Renderer", NULL, NULL);

    //
    double mousex, mousey;
    glfwGetCursorPos(window, &mousex, &mousey);
    lastMousePosition.x = mousex;
    lastMousePosition.y = mousey;

    // Check window was created
    if (!window) {
        std::cout << "ERROR::WINDOW::CREATION_FAILED\n";
        glfwTerminate();
        exit(-1);
    }

    // Set window as main window
    glfwMakeContextCurrent(window);

    // Disable cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  

    // Set callback functions
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, Window::windowResized);
    glfwSetCursorPosCallback(window, Window::mouseMoved);
    glfwSetScrollCallback(window, Window::scrolled);
}

Window::~Window() {
    glfwDestroyWindow(window);
}

void Window::draw(Model& model, Shader& shader) {

    // Update uniforms
    static const std::string projView = "projView";
    shader.setMat4(projView, view.getProjView());
    static const std::string viewPos = "viewPos";
    shader.setVec3(viewPos, view.getPosition());

    
    std::string number;
    for (GLsizei i = 0; i < model.getMeshCount(); i++) {
        const Mesh& mesh = model.getMesh(i);

        GLsizei diffuseNr = 1;
        GLsizei specularNr = 1;

        for (int i = 0; i < mesh.getTextureCount(); i++) {
            // Activate Ith texture
            glActiveTexture(GL_TEXTURE0 + i);

            // retrieve texture number
            const std::string& name = mesh.getTexture(i).getType();

            if (name == "diffuse") {
                static const std::string matDiff = "material.diffuse";
                shader.setInt(matDiff, i);
            } else if (name == "specular") {
                static const std::string matSpec = "material.specular";
                shader.setInt(matSpec, i);
            }

            glBindTexture(GL_TEXTURE_2D, mesh.getTexture(i).getID());
        }

        // Bind VAO
        glBindVertexArray(mesh.getVAO());
        
        // Update uniforms
        static const std::string locTrans = "localTransform";
        shader.setMat4(locTrans, model.getLocalTransform());
        static const std::string matAmb = "material.ambient";
        shader.setVec3(matAmb, mesh.getAmbient());
        static const std::string matShin = "material.shininess";
        shader.setFloat(matShin, mesh.getshininess());

        // Draw vertices
        glDrawElementsInstanced(GL_TRIANGLES, mesh.getVertexCount(), GL_UNSIGNED_INT, 0, model.getInstanceCount());

        // Unbind VAO
        glBindVertexArray(0);
    }
}

void Window::windowResized(GLFWwindow* window, GLsizei width, GLsizei height) {
    // Get window pointer
    Window* win = (Window*)glfwGetWindowUserPointer(window);

    // Update width and height
    win->width = width;
    win->height = height;
    
    // Update view
    win->view.updateViewPort(width, height);
}

void Window::mouseMoved(GLFWwindow* window, double xpos, double ypos) {
    // Get window pointer
    Window* win = (Window*)glfwGetWindowUserPointer(window);
    glm::vec2& lastMousePosition = win->lastMousePosition;

    float xoffset = xpos - lastMousePosition.x;
    float yoffset = lastMousePosition.y - ypos;
    lastMousePosition = glm::vec2(xpos, ypos); 

    const float sensitivity = 0.15f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    win->view.rotate(xoffset, yoffset);
}

void Window::scrolled(GLFWwindow* window, double xoffset, double yoffset) {
    Window* win = (Window*)glfwGetWindowUserPointer(window);
    std::cout << xoffset << " " << yoffset << std::endl;
    win->view.multiplySpeed(std::powf(1.1f, yoffset));
}

void Window::useProgram(GLuint ID) {
    if (currentProgram == ID) return;

    currentProgram = ID;
    glUseProgram(ID);
}

void Window::processInput(float deltaTime) {
    // Escape
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        view.move(deltaTime, 1);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        view.move(deltaTime, 2);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        view.move(deltaTime, 3);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        view.move(deltaTime, 4);
    }
}

void Window::update() {
        glfwSwapBuffers(window);
}

void Window::updateView() {
    view.update();
}