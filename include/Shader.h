#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
  
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#ifndef SHADER_PATH
// File path shaders are stored in relative to the build folder
// ../shaders/ by default
const std::string SHADER_PATH = "../shaders/";
#endif

/// @brief Container for OpenGL's shader program
class Shader {
public:
    unsigned int ID;

    /// @brief Initialises a shader program with read in vertex and fragment shaders
    /// @param vertexPath Path to the vertex shader relative to the SHADER_PATH
    /// @param fragmentPath Path to the fragment shader relative to the SHADER_PATH
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    /// @brief Load a vertex shader from a file
    /// @param fileName Path to the vertex shader relative to the SHADER_PATH
    /// @return Shader ID from glCreateShader
    GLuint loadVertexShader(const std::string& fileName);

    /// @brief Load a fragment shader from a file
    /// @param fileName Path to the fragment shader relative to the SHADER_PATH
    /// @return Shader ID from glCreateShader
    GLuint loadFragmentShader(const std::string& fileName);

    /// @brief Tells OpenGL to use this shader 
    void useProgram();
private:

    /// @brief Reads a shader file into a char*
    /// @param fileName Path to the shader relative to the SHADER_PATH
    /// @param shaderCode char* to store the shader code in
    void getShader(const std::string& fileName, char*& shaderCode);
};

#endif