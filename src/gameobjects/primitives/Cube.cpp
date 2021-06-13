#include "Cube.hpp"
#include <iostream>
#include <string.h>
#include <glm/gtc/matrix_transform.hpp>
#include "gameobjects/components/Renderer.hpp"
#include "glad/glad.h"
#include "utils/AssetPool.hpp"
//TODO: some weird stuff happens when adjusting yaw, pitch, and roll seems to have something to do with scalling being applied
//with model matrix

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
    this->model = glm::mat4(1.0f);
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
    }
    this->updateVectors();
    this->shader->setMat4("model", this->model);
    GameObject::update(dt);
}

void Cube::start() {
    this->generateRenderer();
    GameObject::start();
}

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
    this->model = glm::translate(this->model, pos);
}

void Cube::setWindow(GLFWwindow* window) {
    this->window = window;
}

void Cube::processKeyInput(float dt) {
    float translationSpeed = this->speed * dt;
    float rotSpeedVal = this->rotSpeed * dt;
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
        //return home
        this->position = glm::vec3(0.0f, 0.0f, 0.0f);
        this->objFront = glm::vec3(0.0f, 0.0f, -1.0f);
        this->objUp = glm::vec3(0.0f, 1.0f, 0.0f);
        this->objRight = glm::vec3(1.0f, 0.0f, 0.0f);
        this->model = glm::mat4(1.0f);
        this->yaw = 0.0f;
        this->pitch = 0.0f;
        this->roll = 0.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        this->roll += rotSpeedVal;
        this->rollIsDirty = true;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        this->roll -= rotSpeedVal;
        this->rollIsDirty = true;
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        this->pitch += rotSpeedVal;
        this->pitchIsDirty = true;
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        this->pitch -= rotSpeedVal;
        this->pitchIsDirty = true;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        if (this->yaw + rotSpeedVal > 20.0f) {
            this->yaw = 20.0f;
        } else {
            this->yaw += rotSpeedVal;
        }
        this->yawIsDirty = true;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        if (this->yaw - rotSpeedVal < -20.0f) {
            this->yaw = -20.0f;
        } else {
            this->yaw -= rotSpeedVal;
        }
        this->yawIsDirty = true;
    }
    if (glfwGetKey(window, GLFW_KEY_A) != GLFW_PRESS && this->yaw > 0.0f) {
        if (this->yaw - (rotSpeedVal / 4.0f) < 0.0f) {
            this->yaw = 0.0f;
        } else {
            this->yaw -= rotSpeedVal / 4.0f;
        }
        this->yawIsDirty = true;
    }
    if (glfwGetKey(window, GLFW_KEY_D) != GLFW_PRESS && this->yaw < 0.0f) {
        if (this->yaw + rotSpeedVal / 4.0f > 0.0f) {
            this->yaw = 0;
        } else {
            this->yaw += rotSpeedVal / 4.0f;
        }
        this->yawIsDirty = true;
    }
    if (glfwGetKey(window, GLFW_KEY_W)) {
        this->position += (this->objFront * translationSpeed);
    }
}

void Cube::enableKeyInput() {
    this->keyInputEnabled = true;
}
void Cube::updateVectors() {
    //update up, front, and right vectors
    glm::vec4 v4;
    if (this->rollIsDirty) {
        v4 = glm::vec4(this->objUp.x, this->objUp.y, this->objUp.z, 1.0f);
        glm::mat4 rollRot = glm::rotate(glm::mat4(1.0f), glm::radians(this->roll - this->prevRoll), this->objFront);
        v4 = rollRot * v4;
        this->objUp.x = v4.x, this->objUp.y = v4.y, this->objUp.z = v4.z;
        this->objRight = glm::cross(this->objFront, this->objUp);
        this->rollIsDirty = false;
    }

    if (this->pitchIsDirty) {
        v4 = glm::vec4(this->objFront, 1.0f);
        glm::mat4 pitchRot = glm::rotate(glm::mat4(1.0f), glm::radians(this->pitch - this->prevPitch), this->objRight);
        v4 = pitchRot * v4;
        this->objFront.x = v4.x, this->objFront.y = v4.y, this->objFront.z = v4.z;
        this->objUp = glm::cross(this->objRight, this->objFront);
        this->pitchIsDirty = false;
    }

     if (this->yawIsDirty) {
        v4 = glm::vec4(this->objFront, 1.0f);
        glm::mat4 yawRot = glm::rotate(glm::mat4(1.0f), glm::radians(this->yaw - this->prevYaw), this->objUp);
        v4 = yawRot * v4;
        this->objFront.x = v4.x, this->objFront.y = v4.y, this->objFront.z = v4.z;
        this->objRight = glm::cross(this->objFront, this->objUp);
        this->yawIsDirty = false;
    }
    //ensure still normalized
    glm::normalize(this->objFront);
    glm::normalize(this->objUp);
    glm::normalize(this->objRight);

    //after all vectors have been rotated and the position has been updated we can now use these vectors to define the model matrix
    this->model = glm::mat4(
        glm::vec4(this->objRight, 0.0f), //new x axis (right)
        glm::vec4(this->objUp, 0.0f), //new y axis (up)
        glm::vec4(this->objFront, 0.0f), //new z axis (front)
        glm::vec4(this->position, 1.0f) // new origin (center of cube) 
    );

    // std::cout << this->objRight.x << ", " << this->objUp.x << ", " << this->objFront.x << ", " << this->position.x << std::endl;
    // std::cout << this->objRight.y << ", " << this->objUp.y << ", " << this->objFront.y << ", " << this->position.y << std::endl;
    // std::cout << this->objRight.z << ", " << this->objUp.z << ", " << this->objFront.z << ", " << this->position.z << std::endl;
    // std::cout << "0"              << ", " << "0"           << ", " << "0"              << ", " <<  "1"             <<std::endl;
    //if for some reason we want to chang point of rotation from center we can translate the model matrix
    this->prevYaw = this->yaw;
    this->prevPitch = this->pitch;
    this->prevRoll = this->roll;
}

void Cube::rollRot(float roll) {
    this->roll += roll;
    this->rollIsDirty = true;
}
void Cube::yawRot(float yaw) {
    this->yaw += yaw;
    this->yawIsDirty = true;
}
void Cube::pitchRot(float pitch) {
    this->pitch += pitch;
    this->pitchIsDirty = true;
}

void Cube::addTexture(Texture* tex) {
    // textures.add(tex);
    // this->addComponent(tex);
    // if (textures.getSize() == 1) {
    //     this->generateRenderer();
    // }
}
