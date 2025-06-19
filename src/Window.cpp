#include <Window.h>

#include <iostream>

Window::Window(GLsizei width, GLsizei height)
: width(width), height(height), view(width, height) {

    // Create window
    window = glfwCreateWindow(width, height, "Renderer", NULL, NULL);

    //
    lastMousePosition.x = width / 2;
    lastMousePosition.y = height / 2;

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
}

Window::~Window() {
    glfwDestroyWindow(window);
}

void Window::draw(VertexArray& vertexArray) {
    // Bind VAO
    glBindVertexArray(vertexArray.getVAO());
    
    // Calculate transform
    glm::mat4 transform = view.getProjView() * vertexArray.getWorldTransform();
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, &transform[0].x);
    
    // Draw vertices
    glDrawElements(GL_TRIANGLES, vertexArray.getVertexCount(), GL_UNSIGNED_INT, 0);

    // Unbind VAO
    glBindVertexArray(0);
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

void Window::useProgram(GLuint ID) {
    if (currentProgram == ID) return;

    currentProgram = ID;
    glUseProgram(ID);

    transformLocation = glGetUniformLocation(currentProgram, "transform");

    // Check if get uniform failed
    if (transformLocation == -1) {
        std::cout << "ERROR::SHADER::GET_UNIFORM_FAILED (transform)\n";
        return;
    }
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