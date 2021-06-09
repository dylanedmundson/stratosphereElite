#include "Texture.hpp"
#include "stb/stb_image.h"
#include <glad/glad.h>

void Texture::init(std::string filePath, TEX_TYPE type, IMG_FORMAT imgFormat) {
    this->filePath = filePath;
    glGenTextures(1, &this->texID);
    this->bind();

    //default configs
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);

    if (type == TEX_LINEAR) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    } else { //default to PIXEL
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
    
    int nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = my_stbi_load(filePath.c_str(), &this->width, &this->height, &nrChannels, 0);
    if (data) {
        if (imgFormat == RGBA) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        } else { // default to RGB
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
        stbi_failure_reason();
    }
    stbi_image_free(data);
    this->unbind();
    
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, this->texID);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int Texture::getID() {
    return this->texID;
}

int Texture::getWidth() {
    return width;
}

int Texture::getHeight() {
    return height;
}

void Texture::update(float dt) {
    //TODO: handle animations
}

void Texture::start() {
    Component::start();
}