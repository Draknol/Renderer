#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

#include <string>

/// @brief Container for OpenGL's texture program
class Texture {
private:
    GLuint ID;
    GLuint* instanceCount; // insures glDeleteTextures isn't called early
    std::string type;
    std::string path;
public:
    /// @brief Loads a texture with read in byte array
    /// @param texturePath Path to the image file relative to the TEXTURE_PATH
    /// @param type texture type (eg diffuse)
    Texture(const std::string& texturePath, const std::string& type);
    Texture(const Texture& other);
    Texture& operator=(const Texture& other);
    ~Texture();

    /// @brief Load a texture from a file
    /// @param texturePath Path to the image file relative to the TEXTURE_PATH
    void loadTexture(const std::string& fileName);

    /// @brief Tells OpenGL to use this texture
    /// @brief (binds this texture to GL_TEXTURE0)
    void useTexture();

    /// @brief Gets texture ID from glGenTextures
    GLuint getID() const { return ID; }

    /// @brief Gets texture type (eg diffuse)
    const std::string& getType() const { return type; }

    /// @brief Gets path to image file
    const std::string& getPath() const { return path; }
};

#endif