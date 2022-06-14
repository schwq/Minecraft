#ifndef SHADER_COMPILER
#define SHADER_COMPILER
#include "include.h"
class Shader 
{
public:
    unsigned int shaderProgramID;
    Shader(const char *vertexFilePath, const char*fragmentFilePath);
    template <class type> void setNumberShader(const std::string &name, type value);
    void use();
};

#endif 