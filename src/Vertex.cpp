#include <Vertex.h>

Vertex::Vertex(GLfloat x, GLfloat y, GLfloat z, GLuint color, GLfloat s, GLfloat t)
: x(x), y(y), z(z), color(color), s(s), t(t)
{}

Vertex::Vertex(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat b, GLfloat g, GLfloat a, GLfloat s, GLfloat t) 
: x(x), y(y), z(z), color(rgbaToHex(r, g, b, a)), s(s), t(t)
{}

GLuint Vertex::rgbaToHex(GLfloat r, GLfloat b, GLfloat g, GLfloat a) {
    return (GLuint)(a * 255) << 24 | (GLuint)(b * 255) << 16 | (GLuint)(g * 255) << 8 | (GLuint)(r * 255);
}