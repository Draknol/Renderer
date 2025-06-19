#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <Vertex.h>

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>

static const glm::mat4 DEFAULT_TRANSFORM(1.0f);

/// @brief Container for a VAO, VBO and EBO
class VertexArray {
private:
    GLuint VBO;
    GLuint VAO;
    GLuint EBO;
    GLsizei vertexCount;
    glm::mat4 worldTransform = DEFAULT_TRANSFORM;
public:

    /// @brief Initialise a VertexArray from an array of vertices
    /// @param vertices pointer to vertices
    /// @param vertexSize size of array (in bytes)
    /// @param indices pointer to indices
    /// @param indicesSize size of array (in bytes)
    VertexArray(Vertex* vertices, GLsizei vertexSize, GLuint* indices, GLsizei indicesSize);

    /// @brief Scale object to multiplier * previousSize
    /// @param multiplier Amount to scale by
    void scale(const glm::vec3& multiplier);

    /// @brief Rotate object by angle on an axis
    /// @param angle Angle to rotate by (in radians)
    /// @param axis Axis to rotate on
    void rotate(GLfloat angle, const glm::vec3& axis);

    /// @brief Transform object by given offset
    /// @param offset Amount to move
    void translate(const glm::vec3& offset);

    /// @brief Resets transform to the identitiy matrix
    void resetTransform();

    GLuint getVAO() const { return VAO; }
    const glm::mat4& getWorldTransform() const { return worldTransform; }
    GLsizei getVertexCount() const { return vertexCount; }
};

#endif