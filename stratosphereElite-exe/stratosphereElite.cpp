#include "engine/Shader.hpp"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "engine/Window.hpp"
#include "gameobjects/components/Texture.hpp"
#include "gameobjects/components/Renderer.hpp"
#include "gameobjects/GameObject.hpp"
#include "gameobjects/primitives/Cube.hpp"
#include "engine/Camera.hpp"
using namespace std;

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;
const float speed = 2.5f;
const float rotSpeed = 2.0f;
const char* TITLE = "LearnOpenGL";
float deltaTime = 0.0f;
float lastFrame = 0.0f;

float lastX = 400, lastY = 300; //initail mouse position, initiallized to center screen
float yaw = -90.0f; // to make sure point in - z dir yaw gets 90 degree rotation
float pitch = 0.0f;
bool firstMouse = true;
float zoom = 45.0f;

void processKeyInput(GLFWwindow *window, glm::vec4* vec, float* xRot, float* yRot, float*zRot);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

int main() {
    Window window = Window(WIDTH, HEIGHT, TITLE);
    window.init();

    GameObject* cube = new Cube(new Color(64, 0, 64), 800, 100, 400, WIDTH, HEIGHT, window.getWindow());
    cube->start();
    ((Cube*)cube)->enableKeyInput();
    window.addGameObject(cube);
  
    //================keep for texture abstraction int go
    // renderer->enableTexture();
    
    //upload and configure textures
    // Texture* texture1 = new Texture();
    // texture1->init("assets/wall.jpg", TEX_LINEAR, RGB);
    // Texture* texture2 = new Texture();
    // texture2->init("assets/awesomeface.png", TEX_LINEAR, RGBA);

    // renderer->addTexture(texture1);
    // renderer->addTexture(texture2);
    //================keep for texture abstraction int go

    //set up matrices and vectors for transformations
    glm::vec4 transVec(0.0f, 0.0f, 1.0f, 1.0f);
    glm::mat4 model = glm::mat4(1.0f); //identity matrix 4x4
    glm::mat4 view;
    glm::mat4 projection;

    //TODO: go add set alpha
    // renderer->setAlphaBlend(0.5f);

    float anglex = 0;
    float angley = 0;
    float anglez = 0;

    glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED); //hides cursor and locks it in center
    glfwSetCursorPosCallback(window.getWindow(), mouse_callback); //set mouse callback;
    glfwSetScrollCallback(window.getWindow(), scroll_callback);

    Shader* shader = cube->getShader();
    Camera* camera = new Camera(window.getWindow());
    camera->addShader(shader);
    // camera->addShader(cube2->getShader());
    while (!window.shouldClose()) 
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        //last is we create the direction vector using the pitch and yaw values and update camera front;
        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        camera->setCamerFront(glm::normalize(direction));
        projection = glm::perspective(glm::radians(zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
        
        // send prjection view and model matrices to shader
        shader->setMat4("model", model);
        shader->setMat4("projection", projection);

        camera->update(deltaTime);
        window.update(deltaTime);
    }

    shader->deleteProgram();
    delete cube;
    cube = nullptr;
    delete shader;
    shader = nullptr;
    delete camera;
    camera = nullptr;
    return EXIT_SUCCESS;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    //calculate change in mouse poisition since last callback
    float xOffset = xpos - lastX;
    float yOffset = lastY - ypos; //reversed: y ranges bottom to top
    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.1f;
    xOffset *= sensitivity; //multiply offset by mouse sensitivity
    yOffset *= sensitivity;

    //add these values to the pitch and yaw values
    yaw += xOffset;
    pitch += yOffset;

    //lastly we need to constrain the users to only be able to look up -89 degrees above that we get LookAt flip which causes
    //some weird interfacial issues, we just replace euler value with its constraint
    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    if (pitch < -89.0f) {
        pitch = -89.0f;
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    zoom -= (float) yoffset;
    if (zoom < 1.0f) {
        zoom =  1.0f;
    }
    if (zoom > 45) {
        zoom = 45.0f;
    }
}