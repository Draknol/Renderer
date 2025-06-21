#ifndef MESH_H
#define MESH_H

#include <Vertex.h>
#include <Texture.h>
#include <Shader.h>

#include <vector>

//static const glm::mat4 DEFAULT_TRANSFORM(1.0f);

/// @brief Stores a mesh with vertices, indicies and textures
class Mesh {
private:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    GLuint VAO, VBO, EBO;

    //glm::mat4 worldTransform = DEFAULT_TRANSFORM;

public:

    /// @brief Constructor for mesh
    /// @param vertices Vector of vertices
    /// @param indices Vector of indices
    /// @param textures Vector of Texture pointers (Textures aren't stored locally)
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures);

    GLuint getVAO() const { return VAO; }
    const Texture& getTexture(GLsizei i) const { return textures.at(i); }
    //const glm::mat4& getWorldTransform() const { return worldTransform; }
    GLsizei getVertexCount() const { return indices.size(); }
    GLsizei getTextureCount() const { return textures.size(); }
};

#endif