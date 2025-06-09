#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

#include <string>

#ifndef TEXTURE_PATH
// File path textures are stored in relative to the build folder
// "../textures/" by default
#define TEXTURE_PATH "../textures/"
#endif

/// @brief Container for OpenGL's texture program
class Texture {
private:
    GLuint ID;
public:
    /// @brief Loads a texture with read in byte array
    /// @param texturePath Path to the image file relative to the TEXTURE_PATH
    Texture(const std::string& texturePath);
    ~Texture();

    /// @brief Load a texture from a file
    /// @param texturePath Path to the image file relative to the TEXTURE_PATH
    void loadTexture(const std::string& fileName);

    /// @brief Tells OpenGL to use this texture
    /// (inds this texture to GL_TEXTURE0)
    void useTexture();

    GLuint getID();
};

#endif