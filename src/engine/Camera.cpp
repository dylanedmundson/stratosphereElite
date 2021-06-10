#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "MouseCallbacks.hpp"
#include <GLFW/glfw3.h>


Camera::Camera(GLFWwindow* window, float aspectRatio)
{
    this->aspectRatio = aspectRatio;
    this->cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    this->cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    this->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    this->window = window;
    this->shaders = new ArrayList<Shader*>();
    flightControlsEnabled = false;
    this->projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
}

Camera::~Camera()
{
    delete shaders;
    shaders = nullptr;
}

glm::vec3 Camera::getCameraPos() {
    return this->cameraPos;
}

glm::vec3 Camera::getCameraFront() {
    return this->cameraFront;
}

glm::vec3 Camera::getCameraUp() {
   return this->cameraUp;
}

void Camera::addShader(Shader* shader) {
    this->shaders->add(shader);
}

void Camera::setCameraPos(glm::vec3 vec) {
    this->cameraPos = vec;    
}

void Camera::setCameraUp(glm::vec3 vec) {
    this->cameraUp = vec;
}

void Camera::setCamerFront(glm::vec3 vec) {
    this->cameraFront = vec;

}

void Camera::update(float dt) {
    this->processKeyInput(dt);
    glm::mat4 view = glm::lookAt(
        this->cameraPos,
        this->cameraPos + this->cameraFront,
        this->cameraUp
    );
    int len = shaders->getSize();
    for (int i = 0; i < len; i++) {
        this->shaders->get(i)->setMat4("view", view);
        this->shaders->get(i)->setMat4("projection", this->projection);
    }
}

void Camera::processKeyInput(float dt) {
    if (flightControlsEnabled) {
        float cameraSpeed = speed * dt;
        if (glfwGetKey(this->window, GLFW_KEY_UP) == GLFW_PRESS) {
                this->cameraPos += (cameraSpeed * this->cameraFront);
        }
        if (glfwGetKey(this->window, GLFW_KEY_DOWN) == GLFW_PRESS) {
                this->cameraPos -= (cameraSpeed * this->cameraFront);
        }
        if (glfwGetKey(this->window, GLFW_KEY_LEFT) == GLFW_PRESS) {
                this->cameraPos -= glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * cameraSpeed;
        }
        if (glfwGetKey(this->window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
                this->cameraPos += glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * cameraSpeed;
        }
        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw) * cos(glm::radians(pitch)));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw) * cos(glm::radians(pitch)));
        this->cameraFront = glm::normalize(direction);
        this->projection = glm::perspective(glm::radians(zoom), aspectRatio, 0.1f, 100.0f);
    }
}

void Camera::enableCameraFilightControls() {
    glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(this->window, mouse_callback);
    glfwSetScrollCallback(this->window, scroll_callback);
    flightControlsEnabled = true;
}

void Camera::disableCameraControls() {
    glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetCursorPosCallback(this->window, NULL);
    glfwSetScrollCallback(this->window, NULL);
    flightControlsEnabled = false;
}

void Camera::setAspectRatio(float aspectRatio) {
    this->aspectRatio = aspectRatio;
}

bool Camera::controlsEnabled() {
    return this->flightControlsEnabled;
}