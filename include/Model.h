#ifndef MODEL_H
#define MODEL_H

#ifndef MODEL_PATH
// File path models are stored in relative to the build folder
// "objects/" by default
#define MODEL_PATH "objects/"
#endif

#include <Mesh.h>

#include <assimp/scene.h>

static const glm::mat4 DEFAULT_TRANSFORM(1.0f);

/// @brief Stores a model loaded with assimp
class Model {
private:

    std::vector<Mesh> meshes;
    std::string directory;
    
    std::vector<Texture> loadedTextures;

    std::vector<glm::mat4> instanceTransforms;
    
    GLuint instanceVBO;
    glm::mat4 localTransform = DEFAULT_TRANSFORM;
    GLboolean transformsUpdated = true;

    /// @brief Process a node and all it's children recursivly
    /// @param node Node to process
    void processNode(aiNode* node, const aiScene* scene);

    /// @brief Coverts an aiMesh to a Mesh
    /// @param mesh aiMesh to process
    /// @param materials Scene materials
    /// @return Processed Mesh
    Mesh processMesh(aiMesh* mesh, aiMaterial** materials);

    /// @brief Loads a textures for material (stored locally)
    /// @param material Material to process
    /// @param type Type of texture (eg diffuse)
    /// @param typeName String form of type (eg texture_diffuse)
    /// @return Vector of pointers to loaded textures
    std::vector<Texture> loadMaterialTextures(aiMaterial *material, aiTextureType type, const std::string& typeName);

public:

    /// @brief Load a model
    /// @param fileName Path to the model relative to the MODEL_PATH
    /// @param instanceCount Number of instances wanted
    Model(const std::string& fileName, GLuint instanceCount = 1);

    /// @brief Scale object to multiplier * previousSize
    /// @param multiplier Amount to scale by
    /// @param instance Instance to apply to (-1 for global)
    void scale(const glm::vec3& multiplier, GLint instance = -1);

    /// @brief Rotate object by angle on an axis
    /// @param angle Angle to rotate by (in radians)
    /// @param axis Axis to rotate on
    /// @param instance Instance to apply to (-1 for global)
    void rotate(GLfloat angle, const glm::vec3& axis, GLint instance = -1);

    /// @brief Transform object by given offset
    /// @param offset Amount to move
    /// @param instance Instance to apply to (-1 for global)
    void translate(const glm::vec3& offset, GLint instance = -1);

    /// @brief Resets transform to the identitiy matrix
    /// @param instance Instance to apply to (-1 for global)
    void resetTransform(GLint instance = -1);

    /// @brief Call after changing a worldTransform to send changes to the GPU
    void updateTransforms();

    const Mesh& getMesh(GLsizei i) const { return meshes.at(i); }
    GLsizei getMeshCount() const { return meshes.size(); }
    const glm::mat4& getLocalTransform() const { return localTransform; }
    const std::vector<glm::mat4>& getInstanceTransforms() const {return instanceTransforms; }
    const GLsizei getInstanceCount() const { return instanceTransforms.size(); }

};

#endif