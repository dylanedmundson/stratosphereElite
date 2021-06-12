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
const char* TITLE = "LearnOpenGL";
float deltaTime = 0.0f;
float lastFrame = 0.0f;

//TODO: impelement a way for cubes to have a texture

int main() {
    Window window = Window(WIDTH, HEIGHT, TITLE);
    window.init();

    GameObject* cube = new Cube(new Color(64, 0, 64), 800, 100, 400, WIDTH, HEIGHT, window.getWindow());
    for (int i = 0; i < 100; i++) {
        GameObject* cube2 = new Cube(new Color(0, 64, 64), abs(rand() % 799) + 1, abs(rand() % 799) + 1, abs(rand() % 799) + 1, WIDTH, HEIGHT, window.getWindow());
        ((Cube*)cube2)->setPos(glm::vec3((float)(rand() % 20), (float)(rand() % 20), -(float)(rand() % 100)));
        ((Cube*)cube2)->rollRot((float)(rand() % 360));
        ((Cube*)cube2)->pitchRot((float)(rand() % 360));
        ((Cube*)cube2)->yawRot((float)(rand() % 360));
        cube2->start();
        window.addGameObject(cube2);
    }
    GameObject* skyBox = new Cube(new Color(20, 20, 130), 100 * WIDTH, 100 * WIDTH, 100 * WIDTH, WIDTH, HEIGHT, window.getWindow());
    skyBox->start();
    cube->start();
    ((Cube*)cube)->enableKeyInput();
    window.addGameObject(cube);
    window.addGameObject(skyBox);



    glm::mat4 view;
    glm::mat4 projection;

    Shader* shader = cube->getShader();
    Camera* camera = new Camera(window.getWindow(), (float)WIDTH / (float)HEIGHT);
    camera->addShader(shader);
    camera->attachToGameObject(cube);
    camera->enableCameraFilightControls();

    double updateTimeCount = 0.0;
    while (!window.shouldClose()) 
    {
        // if (glfwGetKey(window.getWindow(), GLFW_KEY_C)) {
        //     camera->detachFromGameObject();
        // }
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        camera->update(deltaTime);
        window.update(deltaTime);
}

    shader->deleteProgram();
    return EXIT_SUCCESS;
}