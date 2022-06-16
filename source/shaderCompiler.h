#ifndef SHADER_COMPILER
#define SHADER_COMPILER
#include "include.h"

class Shader 
{
public:
    unsigned int shaderProgramID;
    Shader(const char *vertexFilePath, const char*fragmentFilePath);
    
    void use();
};

#endif 