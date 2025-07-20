#include <Shader.h>

#include <glm/mat4x4.hpp>

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    GLuint vertex = loadShader(vertexPath, GL_VERTEX_SHADER);
    GLuint fragment = loadShader(fragmentPath, GL_FRAGMENT_SHADER);

    // Create shader program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    // Check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    GLint count;
    glGetProgramiv(ID, GL_ACTIVE_UNIFORMS, &count);

    char name[256]; // Increase size if needed
    for (GLint i = 0; i < count; ++i) {
        GLsizei length;
        GLint size;
        GLenum type;
        glGetActiveUniform(ID, i, sizeof(name), &length, &size, &type, name);

        std::string baseName(name);
        if (size > 1) {
            for (GLint j = 0; j < size; ++j) {
                std::string elementName = baseName;
                elementName = elementName.substr(0, elementName.size() - 3)  + "[" + std::to_string(j) + "]";
                locations.insert_or_assign(elementName, glGetUniformLocation(ID, elementName.c_str()));
            }
        } else {
            locations.insert_or_assign(baseName, glGetUniformLocation(ID, baseName.c_str()));
        }
    }
    
    // Delete shaders
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() {
    glDeleteProgram(ID);
}

GLuint Shader::loadShader(const std::string& fileName, GLenum shaderType) {
    std::ifstream file(SHADER_PATH + std::string("/") + fileName);

    // Check if file failed to open
    if (!file.is_open()) {
        std::cout << "ERROR::SHADER::FILE_OPEN_FAILED (" << SHADER_PATH + fileName << ")\n";
        exit(1);
    }

    std::stringstream ssBuffer;
    ssBuffer << file.rdbuf();
    std::string strBuffer = ssBuffer.str();
    const char* code = strBuffer.c_str();

    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &code, NULL);
    glCompileShader(shader);

    // Check for compilation errors
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        exit(1);
    }

    return shader;
}

void Shader::setMat4(const std::string& name, const glm::mat4& matrix) {
    try {
        glUniformMatrix4fv(locations.at(name), 1, GL_FALSE, &matrix[0].x);
    }
    catch(const std::exception& e) {
        std::cout << "ERROR::SHADER::GET_UNIFORM_FAILED (" + name + ")\n";
    }
    
}

void Shader::setInt(const std::string& name, GLint n) {
    try {
        glUniform1i(locations.at(name), n);
    }
    catch(const std::exception& e) {
        std::cout << "ERROR::SHADER::GET_UNIFORM_FAILED (" + name + ")\n";
    }
}

void Shader::setVec3(const std::string& name, const glm::vec3& vector) {
    try {
        glUniform3fv(locations.at(name), 1, &vector.x);
    }
    catch(const std::exception& e) {
        std::cout << "ERROR::SHADER::GET_UNIFORM_FAILED (" + name + ")\n";
    }
}

void Shader::setFloat(const std::string& name, GLfloat n) {
    try {
        glUniform1f(locations.at(name), n);
    }
    catch(const std::exception& e) {
        std::cout << "ERROR::SHADER::GET_UNIFORM_FAILED (" + name + ")\n";
    }
}