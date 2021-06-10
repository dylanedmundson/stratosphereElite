#include "Cube.hpp"
#include <iostream>
#include <string.h>
#include <glm/gtc/matrix_transform.hpp>
#include "gameobjects/components/Renderer.hpp"
#include "glad/glad.h"
#include "utils/AssetPool.hpp"
float timeElapsed = 0.0f;
Cube::Cube() {
}

Cube::Cube(Color* color, int width, int height, int depth, int winWidth, int winHeight, GLFWwindow* window)
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
    this->objFront = glm::vec3(0.0f, 0.0f, -1.0f);
    this->objUp = glm::vec3(0.0f, 1.0f, 0.0f);
    this->window = window;
    this->keyInputEnabled = false;
    this->trans = glm::mat4(1.0f);
    this->yaw = 0.0f;
    this->pitch = 0.0f;
    this->roll = 0.0f;

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
    if (this->keyInputEnabled) {
        processKeyInput(dt);
        this->shader->setMat4("transform", trans);
    }
    GameObject::update(dt);
    if ((timeElapsed += dt) > 1.0f) {
        std::cout << "x: " << this->objFront.x << ", y: " << this->objFront.y << ", z: " << this->objFront.z << std::endl;
        timeElapsed = 0.0f;
    }
}

void Cube::start() {
    this->generateRenderer();
    GameObject::start();
}

//TODO: overide methods
void Cube::generateRenderer() {
    float wHalf = (float)this->width / (float)this->windowWidth / 2.0f;
    float hHalf = (float)this->height / (float)this->windowWidth / 2.0f;
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
    this->shader = AssetPool::getShader("shaders/primitive");
    // this->shader = new Shader();
    // this->shader->loadShaderSource("shaders/primitive/vertex.glsl", GL_VERTEX_SHADER);
    // this->shader->loadShaderSource("shaders/primitive/fragment.glsl", GL_FRAGMENT_SHADER);
    // this->shader->compileAndLink();
}

void Cube::setPos(glm::vec3 pos) {
    this->position = pos;
}

void Cube::setWindow(GLFWwindow* window) {
    this->window = window;
}

void Cube::processKeyInput(float dt) {
    //TODO: try modeling normalized vector to a circle in its
    // plane and map rotation this way processing rotations into 
    // matricies and vector changes mathematically
    float translationSpeed = this->speed * dt;
    float rotSpeedVal = this->rotSpeed * dt;
    this->trans = glm::mat4(1.0f);
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
        //return home
        this->position = glm::vec3(0.0f, 0.0f, 0.0f);
        this->objFront = glm::vec3(0.0f, 0.0f, -1.0f);
        this->objUp = glm::vec3(0.0f, 1.0f, 0.0f);
        this->yaw = 0.0f;
        this->pitch = 0.0f;
        this->roll = 0.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        this->roll -= rotSpeedVal;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        this->roll += rotSpeedVal;
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        this->pitch += rotSpeedVal;
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        this->pitch -= rotSpeedVal;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        if (this->yaw + rotSpeedVal > 20.0f) {
            this->yaw = 20.0f;
        } else {
            this->yaw += rotSpeedVal;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        if (this->yaw - rotSpeedVal < -20.0f) {
            this->yaw = -20.0f;
        } else {
            this->yaw -= rotSpeedVal;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_A) != GLFW_PRESS && this->yaw > 0.0f) {
        if (this->yaw - (rotSpeedVal / 4.0f) < 0.0f) {
            this->yaw = 0.0f;
        } else {
            this->yaw -= rotSpeedVal / 4.0f;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_D) != GLFW_PRESS && this->yaw < 0.0f) {
        if (this->yaw + rotSpeedVal / 4.0f > 0.0f) {
            this->yaw = 0;
        } else {
            this->yaw += rotSpeedVal / 4.0f;
        }
    }
    glm::vec4 v4Front = glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);
    glm::vec4 v4Up = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    glm::mat4 trans1 = glm::mat4(1.0f);
    trans1 = glm::rotate(trans1, glm::radians(this->pitch), glm::cross(this->objUp, this->objFront));
    glm::mat4 trans2 = glm::mat4(1.0f);
    trans2 = glm::rotate(trans2, glm::radians(this->yaw), this->objUp);
    glm::mat4 trans3 = glm::mat4(1.0f);
    trans3 = glm::rotate(trans3, glm::radians(this->roll), this->objFront);
    v4Front = trans3 * trans2 * trans1 * v4Front;
    v4Up = trans3 * trans2 * trans1 * v4Up;
    this->objFront.x = v4Front.x;
    this->objFront.y = v4Front.y;
    this->objFront.z = v4Front.z;
    this->objUp.x = v4Up.x;
    this->objUp.y = v4Up.y;
    this->objUp.z = v4Up.z;
    this->objFront = glm::normalize(this->objFront);
    this->objUp = glm::normalize(this->objUp);
    if (glfwGetKey(window, GLFW_KEY_W)) {
            this->position += (this->objFront * translationSpeed);
    }
    this->trans = glm::translate(trans, this->position);
    this->trans = glm::rotate(trans, glm::radians(this->pitch), glm::cross(this->objUp, this->objFront));
    this->trans = glm::rotate(trans, glm::radians(this->yaw), this->objUp);
    this->trans = glm::rotate(trans, glm::radians(this->roll), this->objFront);
    std::cout << glm::dot(this->objFront, this->objUp) <<std::endl;
}

void Cube::enableKeyInput() {
    this->keyInputEnabled = true;
}