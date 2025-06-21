#include <Texture.h>

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(const std::string& texturePath, const std::string& type)
: path(texturePath), type(type), instanceCount(new GLuint(1)) {
    loadTexture(texturePath);
}

Texture::Texture(const Texture& other)
    : ID(other.ID), type(other.type), path(other.path), instanceCount(other.instanceCount) {
    ++(*instanceCount);
}

Texture& Texture::operator=(const Texture& other) {
    if (this != &other) {
        ID = other.ID;
        type = other.type;
        path = other.path;
        instanceCount = other.instanceCount;
        (*instanceCount)++;
    }
    return *this;
}

Texture::~Texture() {
    (*instanceCount)--;
    if (instanceCount == 0) {
        glDeleteTextures(1, &ID);
        delete instanceCount;
    }
}

void Texture::loadTexture(const std::string& fileName) {

    // Read from file
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    GLubyte *data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);
    
    // Check for load errors
    if (!data) std::cout << "ERROR::TEXTURE::LOAD_FAILED (" << fileName << ")\n";

    // Create and bind texture
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    
    GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    // Make mipmap
    glGenerateMipmap(GL_TEXTURE_2D);

    // Delete byte array
    stbi_image_free(data);
}

void Texture::useTexture() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ID);
}