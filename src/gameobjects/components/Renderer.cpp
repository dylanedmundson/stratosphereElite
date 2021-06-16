#include "Renderer.hpp"
#include <glad/glad.h>
#include <iostream>
#include <string>
#include "gameobjects/GameObject.hpp"

Renderer::Renderer() {
    this->vertices = nullptr;
    this->hasColor = false;
    this->hasTex = false;
}
Renderer::Renderer(Shader* shader) {
    this->shader = shader;
    this->vertices = nullptr;
    this->hasColor = false;
    this->hasTex = false;
}

void Renderer::setShader(Shader* shader) {
    this->shader = shader;
}

Renderer::~Renderer() {
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
    this->vertices = nullptr;
    this->shader = nullptr;
    this->texture = nullptr;
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
    this->shader->use();
    if (this->hasTex) {
        this->texture = (Texture*)this->getGo()->getComponent(Component::TEXTURE_NAME);
        if (this->texture == nullptr) {
            throw std::runtime_error("ERROR AT RENDERER: texture enabled but not added to object");
        }
        shader->setInt("texture1", 0);
    }
}

void Renderer::setVertices(float* vertices, int sizeofVertices) {
    this->vertices = vertices;
    this->sizeofVertices = sizeofVertices;
}

void Renderer::render() {
    this->shader->use();
    this->shader->setBool("hasTex", this->hasTex);
    if (this->hasTex) {
        glActiveTexture(GL_TEXTURE0);
        this->texture->bind();
    }
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    if (this->hasTex) {
        this->texture->unbind();
    }
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

void Renderer::disableColor() {
    this->hasColor = false;
}

void Renderer::disableTexture() {
    this->hasTex = false;
}

unsigned int Renderer::getVAO() {
    return this->VAO;
}

std::string Renderer::getName() {
    return Component::RENDERER_NAME;
}