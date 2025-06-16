#ifndef VERTEX_H

#include <gl/glew.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

/// @brief A vertex with a position, color and texture coordinates
class Vertex
{
private:
    glm::vec3 pos;
    glm::u8vec4 color;
    glm::vec2 textCoord;
public:

    /// @brief Creates a vertex with given position, color (hex or rgba) and texture coordinates
    Vertex(glm::vec3 pos, glm::u8vec4 color, glm::vec2 textCoord): pos(pos), color(color), textCoord(textCoord) {};
    Vertex(GLfloat x, GLfloat y, GLfloat z, GLuint color, GLfloat s, GLfloat t): pos(x, y, z), color(color >> 24, color >> 16, color >> 8, color), textCoord(s, t) {};

    // Intended for use in glVertexAttribPointer
    static constexpr void* offsetPos() { return (void*)offsetof(Vertex, pos); }
    static constexpr void* offsetColor() { return (void*)offsetof(Vertex, color); }
    static constexpr void* offsetTextCoord() { return (void*)offsetof(Vertex, textCoord); }
};

#endif