#ifndef SHADER_COMPILER
#define SHADER_COMPILER
#include "include.h"

class Shader 
{
public:
    unsigned int shaderProgramID;
    Shader(const char *vertexFilePath, const char*fragmentFilePath);
    
    void use();
    void setMat4(const std::string &name, const glm::mat4 &mat) const;
    void setInt(const std::string &name, int value) const;
};

#endif 