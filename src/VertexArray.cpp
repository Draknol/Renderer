#include <VertexArray.h>

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

VertexArray::VertexArray(Vertex* vertices, GLsizei vertexSize, GLuint* indices, GLsizei indicesSize)
    : vertexCount(indicesSize / sizeof(GLuint)) {

    // Create and bind VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexSize, vertices, GL_STATIC_DRAW);

    // Create and bind VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // EBO
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

    // Apply position attribute to VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), Vertex::offsetPos());
    glEnableVertexAttribArray(0);

    // Apply color attribute to VBO
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), Vertex::offsetColor());
    glEnableVertexAttribArray(1);

    // Apply texture coordinates attribute to VBO
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), Vertex::offsetTextCoord());
    glEnableVertexAttribArray(2);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void VertexArray::scale(const glm::vec3& multiplier) {
    worldTransform = glm::scale(worldTransform, multiplier);
}

void VertexArray::rotate(GLfloat angle, const glm::vec3& axis) {
    worldTransform = glm::rotate(worldTransform, angle, axis);
}

void VertexArray::translate(const glm::vec3& offset) {
    worldTransform = glm::translate(worldTransform, offset);
}

void VertexArray::resetTransform() {
    worldTransform = DEFAULT_TRANSFORM;
}