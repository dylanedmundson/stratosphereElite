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
    this->objRight = glm::vec3(1.0f, 0.0f, 0.0f);
    this->window = window;
    this->keyInputEnabled = false;
    this->trans = glm::mat4(1.0f);
    this->yaw = 0.0f;
    this->pitch = 0.0f;
    this->roll = 0.0f;
    this->prevYaw = 0.0f;
    this->prevPitch = 0.0f;
    this->prevRoll = 0.0f;

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
        std::cout << "yaw: " << this->yaw << ", pitch: " << this->pitch << ", roll: " << this->roll << std::endl;
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
}

void Cube::setPos(glm::vec3 pos) {
    this->position = pos;
}

void Cube::setWindow(GLFWwindow* window) {
    this->window = window;
}

void Cube::processKeyInput(float dt) {
    //TODO: paly arround with controls more to get better input after palyer camera implemented
    float translationSpeed = this->speed * dt;
    float rotSpeedVal = this->rotSpeed * dt;
    // this->trans = glm::mat4(1.0f);
    float yawUpdate = 0.0f;
    float pitchUpdate = 0.0f;
    float rollUpdate = 0.0f;
    bool yawIsDirty = false;
    bool pitchIsDirty = false;
    bool rollIsDirty = false;
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
        rollIsDirty = true;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        this->roll += rotSpeedVal;
        rollIsDirty = true;
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        this->pitch += rotSpeedVal;
        pitchIsDirty = true;
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        this->pitch -= rotSpeedVal;
         pitchIsDirty = true;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        if (this->yaw + rotSpeedVal > 20.0f) {
            this->yaw = 20.0f;
        } else {
            this->yaw += rotSpeedVal;
        }
        yawIsDirty = true;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        if (this->yaw - rotSpeedVal < -20.0f) {
            this->yaw = -20.0f;
        } else {
            this->yaw -= rotSpeedVal;
        }
        yawIsDirty = true;
    }
    if (glfwGetKey(window, GLFW_KEY_A) != GLFW_PRESS && this->yaw > 0.0f) {
        if (this->yaw - (rotSpeedVal / 4.0f) < 0.0f) {
            this->yaw = 0.0f;
        } else {
            this->yaw -= rotSpeedVal / 4.0f;
        }
        yawIsDirty = true;
    }
    if (glfwGetKey(window, GLFW_KEY_D) != GLFW_PRESS && this->yaw < 0.0f) {
        if (this->yaw + rotSpeedVal / 4.0f > 0.0f) {
            this->yaw = 0;
        } else {
            this->yaw += rotSpeedVal / 4.0f;
        }
        yawIsDirty = true;
    }
    //update yaw
    glm::vec4 v4;
    glm::mat4 rotation = glm::mat4(1.0f);
    glm::mat4 rotation2 = glm::mat4(1.0f);
    glm::mat4 rotation3 = glm::mat4(1.0f);
    if (yawIsDirty) {
        v4 = glm::vec4(this->objFront.x, this->objFront.y, this->objFront.z, 1.0f);
        rotation = glm::rotate(rotation, glm::radians(this->yaw - this->prevYaw), this->objUp);
        this->trans = this->trans * rotation;
        v4 = rotation * v4;
        this->objFront.x = v4.x;
        this->objFront.y = v4.y;
        this->objFront.z = v4.z;
        this->objRight = glm::cross(this->objFront, this->objUp);
    }

    //update pitch
    if (pitchIsDirty) {
        v4 = glm::vec4(this->objFront.x, this->objFront.y, this->objFront.z, 1.0f);
        rotation2 = glm::rotate(rotation2, glm::radians(this->pitch - this->prevPitch), this->objRight);
        this->trans = this->trans * rotation2;
        v4 = rotation2 * v4;
        this->objFront.x = v4.x, this->objFront.y = v4.y, this->objFront.z = v4.z;
        this->objUp = glm::cross(this->objRight, this->objFront);
    }

    //update roll
    if (rollIsDirty) {
        v4 = glm::vec4(this->objUp.x, this->objUp.y, this->objUp.z, 1.0f);
        rotation3 = glm::rotate(rotation3, glm::radians(this->roll - this->prevRoll), this->objFront);
        this->trans = this->trans * rotation3;
        v4 = rotation3 * v4;
        this->objUp.x = v4.x, this->objUp.y = v4.y, this->objUp.z = v4.z;
        this->objRight = glm::cross(this->objFront, this->objUp);
    }

    //ensure still normalized
    glm::normalize(this->objFront);
    glm::normalize(this->objUp);
    glm::normalize(this->objRight);

     if (glfwGetKey(window, GLFW_KEY_W)) {
        this->position += (this->objFront * translationSpeed);
        this->trans = glm::translate(trans, this->objFront * translationSpeed);
    }
    //update image
    // trans = trans * rotation3 * rotation2 * rotation1;
    // this->trans = glm::rotate(trans, glm::radians(this->yaw - this->prevYaw), this->objUp);;
    // this->trans = glm::rotate(trans, glm::radians(this->yaw),  glm::vec3(0.0f, 1.0f, 0.0f));
    // this->trans = glm::rotate(trans, glm::radians(this->roll),  glm::vec3(0.0f, 0.0f, 1.0f));

    // glm::vec4 v4Front = glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);
    // glm::mat4 trans1 = glm::mat4(1.0f);
    // trans1 = glm::rotate(trans1, glm::radians(this->pitch), glm::vec3(1.0f, 0.0f, 0.0f));
    // glm::mat4 trans2 = glm::mat4(1.0f);
    // trans2 = glm::rotate(trans2, glm::radians(this->yaw), glm::vec3(0.0f, 1.0f, 0.0f));
    // glm::mat4 trans3 = glm::mat4(1.0f);
    // trans3 = glm::rotate(trans3, glm::radians(this->roll), glm::vec3(0.0f, 0.0f, 1.0f));
    // v4Front = trans3 * trans2 * trans1 * v4Front;
    // this->objFront.x = v4Front.x;
    // this->objFront.y = v4Front.y;
    // this->objFront.z = v4Front.z;
    // this->objFront = glm::normalize(this->objFront);
    this->prevYaw = this->yaw;
    this->prevPitch = this->pitch;
    this->prevRoll = this->roll;
}

void Cube::enableKeyInput() {
    this->keyInputEnabled = true;
}