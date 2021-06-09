#include "Cube.hpp"
#include <iostream>
#include <string.h>
#include <glm/gtc/matrix_transform.hpp>
#include "gameobjects/components/Renderer.hpp"
#include "glad/glad.h"

Cube::Cube() {
}

Cube::Cube(Color* color, int width, int height, int depth, int winWidth, int winHeight)
{
    if (width <= 0 || height <= 0) {
        std::string errMsg = "improper heigh or width input, must be > 0";
        throw std::runtime_error(errMsg.c_str());
    }
    this->c = color;
    this->width = width;
    this->height = height;
    this->windowWidth = winWidth;
    this->windowHeight = winHeight;
    this->depth = depth;
    this->position = glm::vec3(0.0f, 0.0f, 0.0f);
}

Cube::~Cube()
{
    delete this->c;
    this->c = nullptr;
}

void Cube::setWidth(int width) {
    this->width = width;

}
void Cube::setHeight(int height) {
    this->height = height;
}
void Cube::setDepth(int depth) {
    this->depth = depth;
}
void Cube::setWindowWidth(int winWidth) {
    this->windowWidth = winWidth;
}
void Cube::setWindowHeight(int winHeight) {
    this->windowHeight = winHeight;
}

void Cube::update(float dt) {
    this->shader->use();
    // glm::mat4 trans = glm::mat4(1.0f);
    // trans = glm::translate(trans, this->position);
    // shader->setMat4("transform", trans);
    GameObject::update(dt);
}

void Cube::start() {
    this->generateRenderer();
    GameObject::start();
}

//TODO: overide methods
void Cube::generateRenderer() {
    float wHalf = (float)this->width / (float)this->windowWidth / 2.0f;
    float hHalf = (float)this->height / (float)this->windowHeight / 2.0f;
    float dHalf = (float)this->depth / (float)this->windowWidth / 2.0f;
    float r = (float)this->c->getRedf();
    float g = (float)this->c->getGreenf();
    float b = (float)this->c->getBluef();
    float shade = 0.1;
    float* vertices = new float[216]{
        //position                  //vert color
        //front face
        -wHalf, -hHalf,  dHalf,     r, g, b,
        -wHalf,  hHalf,  dHalf,     r, g, b,
         wHalf,  hHalf,  dHalf,     r, g, b,
         wHalf,  hHalf,  dHalf,     r, g, b,
        -wHalf, -hHalf,  dHalf,     r, g, b,
         wHalf, -hHalf,  dHalf,     r, g, b,

        //back face
        -wHalf, -hHalf, -dHalf,     r, g, b,
        -wHalf,  hHalf, -dHalf,     r, g, b,
         wHalf,  hHalf, -dHalf,     r, g, b,
         wHalf,  hHalf, -dHalf,     r, g, b,
        -wHalf, -hHalf, -dHalf,     r, g, b,
         wHalf, -hHalf, -dHalf,     r, g, b,
        //left face
        -wHalf,  hHalf,  dHalf,     r + shade, g + shade, b + shade,
        -wHalf, -hHalf,  dHalf,     r + shade, g + shade, b + shade,
        -wHalf, -hHalf, -dHalf,     r + shade, g + shade, b + shade,
        -wHalf,  hHalf,  dHalf,     r + shade, g + shade, b + shade,
        -wHalf, -hHalf, -dHalf,     r + shade, g + shade, b + shade,
        -wHalf,  hHalf, -dHalf,     r + shade, g + shade, b + shade,

        //right face
         wHalf,  hHalf,  dHalf,     r + shade, g + shade, b + shade,
         wHalf, -hHalf,  dHalf,     r + shade, g + shade, b + shade,
         wHalf, -hHalf, -dHalf,     r + shade, g + shade, b + shade,
         wHalf,  hHalf,  dHalf,     r + shade, g + shade, b + shade,
         wHalf, -hHalf, -dHalf,     r + shade, g + shade, b + shade,
         wHalf,  hHalf, -dHalf,     r + shade, g + shade, b + shade,

        //top face
        -wHalf,  hHalf,  dHalf,     r - shade, g - shade, b - shade,
        -wHalf,  hHalf, -dHalf,     r - shade, g - shade, b - shade,
         wHalf,  hHalf,  dHalf,     r - shade, g - shade, b - shade,
         wHalf,  hHalf,  dHalf,     r - shade, g - shade, b - shade,
        -wHalf,  hHalf, -dHalf,     r - shade, g - shade, b - shade,
         wHalf,  hHalf, -dHalf,     r - shade, g - shade, b - shade,

        //top face
        -wHalf, -hHalf,  dHalf,     r - shade, g - shade, b - shade,
        -wHalf, -hHalf, -dHalf,     r - shade, g - shade, b - shade,
         wHalf, -hHalf,  dHalf,     r - shade, g - shade, b - shade,
         wHalf, -hHalf,  dHalf,     r - shade, g - shade, b - shade,
        -wHalf, -hHalf, -dHalf,     r - shade, g - shade, b - shade,
         wHalf, -hHalf, -dHalf,     r - shade, g - shade, b - shade
    };
    generateShader();
    this->renderer = new Renderer(this->shader);
    this->renderer->setVertices(vertices, 216);
    this->renderer->setUsage(GL_STATIC_DRAW);
    this->renderer->enableColor();
    components->add(this->renderer);
}

void Cube::generateShader() {
    this->shader = new Shader();
    this->shader->loadShaderSource("shaders/primitive/vertex.glsl", GL_VERTEX_SHADER);
    this->shader->loadShaderSource("shaders/primitive/fragment.glsl", GL_FRAGMENT_SHADER);
    this->shader->compileAndLink();
}

