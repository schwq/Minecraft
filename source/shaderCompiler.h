#ifndef SHADER_COMPILER
#define SHADER_COMPILER
#include "include.h"
class Shader 
{
public:
    unsigned int shaderProgramID;
    Shader(const char *vertexFilePath, const char*fragmentFilePath);

    void use();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;


};

#endif 