#include <Window.h>

#include <iostream>

Window::Window(GLsizei width, GLsizei height)
: width(width), height(height), view(width, height) {

    // Create window
    window = glfwCreateWindow(width, height, "Renderer", NULL, NULL);

    // Check window was created
    if (!window) {
        std::cout << "ERROR::WINDOW::CREATION_FAILED\n";
        glfwTerminate();
        exit(-1);
    }

    // Set window as main window
    glfwMakeContextCurrent(window);

    // Set function to be called on size change
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, Window::windowResized);
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
    win->view.update(width, height);
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

void Window::processInput() {
    // Escape
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void Window::update() {
        glfwSwapBuffers(window);
}