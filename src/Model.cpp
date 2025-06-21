#include <Model.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <iostream>

Model::Model(const std::string& fileName) {
    // Load scene
    std::string path = MODEL_PATH + std::string("/") + fileName;
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    // Check scene loaded correctly
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    // Save file directory
    directory = path.substr(0, path.find_last_of('/') + 1);

    // Process nodes recursively
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene) {
    // Process meshes
    for(GLsizei i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]]; 
        meshes.push_back(processMesh(mesh, scene->mMaterials));			
    }

    // Recurse over children
    for(GLsizei i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh* mesh, aiMaterial** materials) {
    // Vertices
    std::vector<Vertex> vertices;
    for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
        // Position
        aiVector3D vec3D = mesh->mVertices[i];
        glm::vec3 position(vec3D.x, vec3D.y, vec3D.z);

        // Texture coords
        glm::vec2 textureCoords(0.0f);
        if (materials[0]) textureCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);

        // Add vertex
        vertices.emplace_back(position, glm::u8vec4(0xFF), textureCoords);
    }

    // Indices
    std::vector<GLuint> indices;
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        // Faces indices
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    // Materials
    std::vector<Texture> textures;
    if(mesh->mMaterialIndex >= 0) {
        aiMaterial* material = materials[mesh->mMaterialIndex];

        // Diffuse
        std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    }

    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial *material, aiTextureType type, const std::string& typeName) {
    std::vector<Texture> textures;

    // Create all textures
    for(GLsizei i = 0; i < material->GetTextureCount(type); i++) {
        aiString path;
        material->GetTexture(type, i, &path);

        // Check if it's already loaded
        bool isLoaded = false;
        for (Texture& loadedTexture : loadedTextures) {
            if (loadedTexture.getPath() == directory + path.C_Str()) {
                textures.push_back(loadedTexture);
                isLoaded = true;
                break;
            }
        }

        // If not, load it
        if (!isLoaded) {
            loadedTextures.emplace_back(directory + path.C_Str(), typeName);
            textures.push_back(loadedTextures.back());
        }
    }

    return textures;
}