#ifndef VERTEX_ARRAY_H

#include <Vertex.h>

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>

static const glm::mat4 DEFAULT_TRANSFORM(1.0f);

class VertexArray {
private:
    GLuint VBO;
    GLuint VAO;
    GLuint EBO;
    GLsizei vertexCount;
    glm::mat4 worldTransform = DEFAULT_TRANSFORM;
public:
    VertexArray(Vertex* vertices, GLsizei vertexSize, GLuint* indices, GLsizei indicesSize);
    void scale(const glm::vec3& multiplier);
    void rotate(GLfloat angle, const glm::vec3& axis);
    void translate(const glm::vec3& offset);
    void resetTransform();
    void draw(GLFWwindow* window);
};

#endif