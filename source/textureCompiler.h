#ifndef TEXTURE_COMPILER
#define TEXTURE_COMPILER
#include "include.h"

class Texture {
public:
    Texture(const char* texturePath);
    int width, height, nrChannels;
};

#endif 