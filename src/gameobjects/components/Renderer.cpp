#include "Renderer.hpp"
#include <glad/glad.h>
#include <iostream>
#include <string>

Renderer::Renderer() {
    this->vertices = nullptr;
    this->hasColor = false;
    this->hasTex = false;
    this->alphaBlend = 0;
    this->textures = new ArrayList<Texture*>();
}
Renderer::Renderer(Shader* shader) {
    this->shader = shader;
    this->vertices = nullptr;
    this->hasColor = false;
    this->hasTex = false;
    this->alphaBlend = 0;
    this->textures = new ArrayList<Texture*>();
}

void Renderer::setShader(Shader* shader) {
    this->shader = shader;
}

void Renderer::addTexture(Texture* tex) {
    this->textures->add(tex);
}

Renderer::~Renderer() {
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
    vertices = nullptr;
    shader = nullptr;
    delete this->textures;
    this->textures = nullptr;
}

void Renderer::update(float dt) {
    //TODO: change so we only update objects data and info to batch renderer
    //so we only send data to GPU once per update (this will greatly improve performance)
    //this way will cause GPU data to be sent each update iteration which will be combersome
    this->render();
}

void Renderer::start() {
    if (this->vertices == nullptr) {
        std::runtime_error("Component.Renderer.start() vertices not initialized");
    }
    float vertBuffer[this->sizeofVertices];
    for (int i = 0; i < sizeofVertices; i++) {
        vertBuffer[i] = *(this->vertices + i);
    }
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);

    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertBuffer), vertBuffer, usage);

    if (hasColor && !hasTex) {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    } else if (hasTex && !hasColor) {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    } else if (hasTex && hasColor) {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)3);
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }
    int texLen = this->textures->getSize();
    this->shader->use();
    for (int i = 0; i < texLen; i++) {
        std::string texName = "texture";
        std::string val = std::to_string(i + 1);
        texName += val;
        std::cout << texName << std::endl;
        shader->setInt(texName.c_str(), i);
    }
    shader->setFloat("alphaBlend", this->alphaBlend);
}

void Renderer::setVertices(float* vertices, int sizeofVertices) {
    this->vertices = vertices;
    this->sizeofVertices = sizeofVertices;
}

void Renderer::render() {
    this->shader->use();
    int texLen = this->textures->getSize();
    this->shader->setInt("hasTex", this->hasTex);
    for (int i = 0; i < texLen; i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        this->textures->get(i)->bind();
    }
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void Renderer::enableColor() {
    this->hasColor = true;
}

void Renderer::enableTexture() {
    this->hasTex = true;
}

void Renderer::setUsage(GLenum usage) {
    this->usage = usage;
}

void Renderer::setAlphaBlend(float alpha) {
    this->alphaBlend = alpha;
}

void Renderer::disableColor() {
    this->hasColor = false;
}

void Renderer::disableTexture() {
    this->hasTex = false;
}

unsigned int Renderer::getVAO() {
    return this->VAO;
}