#include <GL/glew.h>

/// @brief A vertex with a position, color and texture coordinates
class Vertex
{
private:
    GLfloat x, y, z;
    GLuint color;
    GLfloat s, t;
public:

    /// @brief Creates a vertex with given position, color (hex or rgba) and texture coordinates
    Vertex(GLfloat x, GLfloat y, GLfloat z, GLuint color, GLfloat s, GLfloat t);
    Vertex(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat b, GLfloat g, GLfloat a, GLfloat s, GLfloat t);

    /// @brief Converts 4 floats in range 0-1 to hex
    /// @return uint of form aabbggrr
    GLuint rgbaToHex(GLfloat r, GLfloat b, GLfloat g, GLfloat a);

    // Intended for use in glVertexAttribPointer
    static constexpr void* offsetPos() { return (void*)offsetof(Vertex, x); }
    static constexpr void* offsetColor() { return (void*)offsetof(Vertex, color); }
    static constexpr void* offsetTextCoord() { return (void*)offsetof(Vertex, s); }
};