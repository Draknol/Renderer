#include <Shader.h>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    GLuint vertex = loadVertexShader(vertexPath);
    GLuint fragment = loadFragmentShader(fragmentPath);

    // Create shader program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    // Check for errors
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

GLuint Shader::loadVertexShader(const std::string& fileName) {
    char* vertexCode;
    getShader(fileName, vertexCode);

    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, NULL);
    glCompileShader(vertex);

    // Check for errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return vertex;
}

GLuint Shader::loadFragmentShader(const std::string& fileName) {
    char* fragmentCode;
    getShader(fileName, fragmentCode);

    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentCode, NULL);
    glCompileShader(fragment);

    // Check for errors
    int success;
    char infoLog[512];
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return fragment;
}

void Shader::getShader(const std::string& fileName, char*& shaderCode) {
    std::ifstream file(SHADER_PATH + fileName, std::ios::binary | std::ios::ate);
    
    // Check for errors
    if (!file.is_open()) {
        std::cout << "ERROR::SHADER::FILE_OPEN_FAILED\n";
        shaderCode = nullptr;
        return;
    }

    // Get end position, move to begining
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    // Read file
    shaderCode = new char[size];
    if (!file.read(shaderCode, size)) {
        std::cout << "ERROR::SHADER::FILE_READ_FAILED\n";
        delete[] shaderCode;
    }
}

void Shader::useProgram() {
    glUseProgram(ID);
}