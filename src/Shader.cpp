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

void Shader::setMat4(const char* name, const glm::mat4& matrix) {
    // Cache location
    if (!locations.count(name)) {
        locations.insert_or_assign(name, glGetUniformLocation(ID, name));
    }

    GLuint location = locations.at(name);

    // Check if get uniform failed
    if (location == -1) {
        std::cout << "ERROR::SHADER::GET_UNIFORM_FAILED (" << name << ")\n";
        return;
    }

    glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0].x);
}

void Shader::setInt(const char* name, GLint n) {
    // Cache location
    if (!locations.count(name)) {
        locations.insert_or_assign(name, glGetUniformLocation(ID, name));
    }

    GLuint location = locations.at(name);

    // Check if get uniform failed
    if (location == -1) {
        std::cout << "ERROR::SHADER::GET_UNIFORM_FAILED (" << name << ")\n";
        return;
    }

    glUniform1i(location, n);
}

void Shader::setVec3(const char* name, const glm::vec3& vector) {
    // Cache location
    if (!locations.count(name)) {
        locations.insert_or_assign(name, glGetUniformLocation(ID, name));
    }

    GLuint location = locations.at(name);

    // Check if get uniform failed
    if (location == -1) {
        std::cout << "ERROR::SHADER::GET_UNIFORM_FAILED (" << name << ")\n";
        return;
    }

    glUniform3fv(location, 1, &vector.x);
}

void Shader::setFloat(const char* name, GLfloat n) {
    // Cache location
    if (!locations.count(name)) {
        locations.insert_or_assign(name, glGetUniformLocation(ID, name));
    }

    GLuint location = locations.at(name);

    // Check if get uniform failed
    if (location == -1) {
        std::cout << "ERROR::SHADER::GET_UNIFORM_FAILED (" << name << ")\n";
        return;
    }

    glUniform1f(location, n);
}