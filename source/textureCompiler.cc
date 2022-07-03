#include "textureCompiler.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../libraries/stb_image.h"
#include <iostream>

Texture::Texture(const char* texturePath) {
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        std::cout << "SUCCESS: Texture loaded with success \n";
    } else {
        std::cout << "ERROR: Texture cannot be loaded\n";
    }
    stbi_image_free(data);
}