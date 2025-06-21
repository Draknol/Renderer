#ifndef MODEL_H
#define MODEL_H

#ifndef MODEL_PATH
// File path models are stored in relative to the build folder
// "objects/" by default
#define MODEL_PATH "objects/"
#endif

#include <Mesh.h>

#include <assimp/scene.h>

/// @brief Stores a model loaded with assimp
class Model {
private:

    std::vector<Mesh> meshes;
    std::string directory;
    
    std::vector<Texture> loadedTextures;

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
    Model(const std::string& fileName);

    const Mesh& getMesh(GLsizei i) const { return meshes.at(i); }
    GLsizei getMeshCount() const { return meshes.size(); }

};

#endif