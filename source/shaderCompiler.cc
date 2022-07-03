#include <fstream>
#include <typeinfo>
#include "shaderCompiler.h"

unsigned int vertexShader;
unsigned int fragmentShader;

Shader::Shader(const char *vertexFilePath, const char*fragmentFilePath) {
    std::ifstream vertexFile = std::ifstream(vertexFilePath, std::ios_base::in|std::ios::ate);
    if(vertexFile.is_open()) {
        auto vertexFileSize = vertexFile.tellg();
        std::cout << "INFO: Vertex shader file size: " << vertexFileSize << std::endl;
        vertexFile.seekg(std::ios::beg);
        std::string vertexContent(vertexFileSize, 0);
        vertexFile.read(&vertexContent[0], vertexFileSize);

        const char *vertexshaderSource = vertexContent.c_str();

        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexshaderSource, NULL);
        glCompileShader(vertexShader);

        int vertex_shader_success_compiled;
        char vertex_infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertex_shader_success_compiled);

        if(!vertex_shader_success_compiled) {
            glGetShaderInfoLog(vertexShader, 512, NULL, vertex_infoLog);
            std::cout << "ERROR: Vertex shader compilation failed!\n" << vertex_infoLog << std::endl;
        } else {
            std::cout << "SUCCESS: vertex shader compilation succeeded!" << std::endl;
        }

        vertexFile.close();
    }
    else {
        std::cout << "ERROR: Cannot read vertex shader" << std::endl;
    }

    std::ifstream fragmentFile = std::ifstream(fragmentFilePath, std::ios_base::in|std::ios::ate);
    if(fragmentFile.is_open()) {
        auto fragmentFileSize = fragmentFile.tellg();
        std::cout << "INFO: Fragment shader file size: " << fragmentFileSize << std::endl;
        fragmentFile.seekg(std::ios::beg);
        std::string fragmentContent(fragmentFileSize, 0);
        fragmentFile.read(&fragmentContent[0], fragmentFileSize);

        const char *fragmentshaderSource = fragmentContent.c_str();

        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentshaderSource, NULL);
        glCompileShader(fragmentShader);

        int fragment_shader_success_compiled;
        char fragment_infoLog[512];
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragment_shader_success_compiled);

        if(!fragment_shader_success_compiled) {
            glGetShaderInfoLog(fragmentShader, 512, NULL, fragment_infoLog);
            std::cout << "ERROR: Fragment shader compilation failed!\n" << fragment_infoLog << std::endl;
        } else {
            std::cout << "SUCCESS: Fragment shader compilation succeeded!" << std::endl;
        }

        fragmentFile.close();
    }
    else {
        std::cout << "ERROR: cannot read fragment shader" << std::endl;
    }

    shaderProgramID = glCreateProgram();
    glAttachShader(shaderProgramID, vertexShader);
    glAttachShader(shaderProgramID, fragmentShader);
    glLinkProgram(shaderProgramID);

    int linking_success;
    char linking_infoLog[512];
    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &linking_success);
    if(!linking_success){
        glGetProgramInfoLog(shaderProgramID, 512, NULL, linking_infoLog);
    } else {
        std::cout << "SUCCESS: ProgramID linking succeeded!" << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use() {
    glUseProgram(shaderProgramID);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const {
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(shaderProgramID, name.c_str()), value); 
}