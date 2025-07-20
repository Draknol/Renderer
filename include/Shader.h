#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
  
#include <string>
#include <unordered_map>

#ifndef SHADER_PATH
// File path shaders are stored in relative to the build folder
// "shaders/" by default
#define SHADER_PATH "shaders/"
#endif

/// @brief Container for OpenGL's shader program
class Shader {
private:
    GLuint ID;
    std::unordered_map<std::string, GLuint> locations;

    /// @brief Reads a shader file into a string
    /// @param fileName Path to the shader relative to the SHADER_PATH
    /// @param shaderCode string to store the shader code in
    void getShader(const std::string& fileName, std::string& shaderCode);
public:
    /// @brief Initialises a shader program with read in vertex and fragment shaders
    /// @param vertexPath Path to the vertex shader relative to the SHADER_PATH
    /// @param fragmentPath Path to the fragment shader relative to the SHADER_PATH
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    /// @brief Load a vertex shader from a file
    /// @param fileName Path to the vertex shader relative to the SHADER_PATH
    /// @param shaderType GLenum for type of shader (eg Gl_VERTEX_SHADER)
    /// @return Shader ID from glCreateShader
    GLuint loadShader(const std::string& fileName, GLenum shaderType);

    /// @brief Tells OpenGL to use this shader 
    void useProgram() const;

    /// @brief Gets program ID from glCreateProgram 
    GLuint getID() const { return ID; }

    /// @brief Set a 4x4 matrix uniform (call useProgram first)
    void setMat4(const std::string& name, const glm::mat4& matrix);

    /// @brief Set a int uniform (call useProgram first)
    void setInt(const std::string& name, GLint n);

    /// @brief Set a vec3 uniform (call useProgram first)
    void setVec3(const std::string& name, const glm::vec3& vector);

    /// @brief Set a float uniform (call useProgram first)
    void setFloat(const std::string& name, GLfloat n);
};

#endif