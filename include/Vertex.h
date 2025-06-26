#ifndef VERTEX_H
#define VERTEX_H

#include <gl/glew.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

/// @brief A vertex with a position, normal and texture coordinates
class Vertex
{
private:
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 textCoord;
public:

    /// @brief Creates a vertex with given position, normal and texture coordinates
    Vertex(glm::vec3 pos, glm::vec3 normal, glm::vec2 textCoord): pos(pos), normal(normal), textCoord(textCoord) {};
    Vertex(GLfloat x, GLfloat y, GLfloat z, GLfloat nx, GLfloat ny, GLfloat nz , GLfloat s, GLfloat t): pos(x, y, z), normal(nx, ny, nz), textCoord(s, t) {};

    // Intended for use in glVertexAttribPointer
    static constexpr void* offsetPos() { return (void*)offsetof(Vertex, pos); }
    static constexpr void* offsetNormal() { return (void*)offsetof(Vertex, normal); }
    static constexpr void* offsetTextCoord() { return (void*)offsetof(Vertex, textCoord); }
};

#endif