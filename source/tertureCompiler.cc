#include "textureCompiler.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../libraries/stb_image.h"

Texture::Texture(const char* texturePath) {
    unsigned char *data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        printf("TEXTURE LOADED SUCCESSED\n");
    } else {
        printf("FAILED TO LOAD TEXTURE\n");
    }
    stbi_image_free(data);
}