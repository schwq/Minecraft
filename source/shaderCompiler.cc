#include "include.h"
#include <fstream>
#include <iostream>
#include "shaderCompiler.h"

unsigned int vertexShader;
unsigned int fragmentShader;

GLuint shaderCompiler(const char *vertexFilePath, const char*fragmentFilePath) {
    std::ifstream vertexFile = std::ifstream(vertexFilePath, std::ios_base::in|std::ios::ate);
    if(vertexFile.is_open()) {
        auto vertexFileSize = vertexFile.tellg();
        std::cout << "Vertex shader file size: " << vertexFileSize << std::endl;
        vertexFile.seekg(std::ios::beg);
        std::string vertexContent(vertexFileSize, 0);
        vertexFile.read(&vertexContent[0], vertexFileSize);

        const char *vertexshaderSource = vertexContent.c_str();
        std::cout << "Vertex Shader Code: \n" << vertexshaderSource << std::endl;

        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexshaderSource, NULL);
        glCompileShader(vertexShader);

        int vertex_shader_success_compiled;
        char vertex_infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertex_shader_success_compiled);

        if(!vertex_shader_success_compiled) {
            glGetShaderInfoLog(vertexShader, 512, NULL, vertex_infoLog);
            std::cout << "ERROR, VERTEX SHADER COMPILATION FAILED\n" << vertex_infoLog << std::endl;
        } else {
            std::cout << "Vertex Shader Compilation Succeeded!" << std::endl;
        }

        vertexFile.close();
    }
    else {
        std::cout << "Error reading vertex shader" << std::endl;
    }

    std::ifstream fragmentFile = std::ifstream(fragmentFilePath, std::ios_base::in|std::ios::ate);
    if(fragmentFile.is_open()) {
        auto fragmentFileSize = fragmentFile.tellg();
        std::cout << "Fragment shader file size: " << fragmentFileSize << std::endl;
        fragmentFile.seekg(std::ios::beg);
        std::string fragmentContent(fragmentFileSize, 0);
        fragmentFile.read(&fragmentContent[0], fragmentFileSize);

        const char *fragmentshaderSource = fragmentContent.c_str();
        std::cout << "Fragment Shader Code: \n" << fragmentshaderSource << std::endl;

        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentshaderSource, NULL);
        glCompileShader(fragmentShader);

        int fragment_shader_success_compiled;
        char fragment_infoLog[512];
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragment_shader_success_compiled);

        if(!fragment_shader_success_compiled) {
            glGetShaderInfoLog(fragmentShader, 512, NULL, fragment_infoLog);
            std::cout << "ERROR, FRAGMENT SHADER COMPILATION FAILED\n" << fragment_infoLog << std::endl;
        } else {
            std::cout << "Fragment Shader Compilation Succeeded!" << std::endl;
        }

        fragmentFile.close();
    }
    else {
        std::cout << "Error reading fragment shader" << std::endl;
    }

    unsigned int shaderProgramID;
    shaderProgramID = glCreateProgram();
    glAttachShader(shaderProgramID, vertexShader);
    glAttachShader(shaderProgramID, fragmentShader);
    glLinkProgram(shaderProgramID);

    int linking_success;
    char linking_infoLog[512];
    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &linking_success);
    if(!linking_success){
        glGetProgramInfoLog(shaderProgramID, 512, NULL, linking_infoLog);
    }

    glUseProgram(shaderProgramID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgramID;
}