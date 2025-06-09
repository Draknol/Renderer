#include <Texture.h>

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(const std::string& texturePath) {
    loadTexture(TEXTURE_PATH + texturePath);
}

Texture::~Texture() {
    glDeleteTextures(1, &ID);
}

void Texture::loadTexture(const std::string& fileName) {

    // Read from file
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    GLubyte *data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);
    if (!data) std::cout << "ERROR::TEXTURE::LOAD_FAILED";

    // Create and bind texture
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    // Make mipmap
    glGenerateMipmap(GL_TEXTURE_2D);

    // Delete byte array
    stbi_image_free(data);
}

void Texture::useTexture() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ID);
}

GLuint Texture::getID() {
    return ID;
}