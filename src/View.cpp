#include <View.h>

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

View::View(float width, float height) {
    view = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    update(width, height);
}

void View::update(float width, float height) {
    aspectRatio = width / height;
    glViewport(0, 0, width, height);
    projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
    projView = projection * view;
}