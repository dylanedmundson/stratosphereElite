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

int main() {
    Window window = Window(WIDTH, HEIGHT, TITLE);
    window.init();

    GameObject* cube = new Cube(new Color(64, 0, 64), 800, 100, 400, WIDTH, HEIGHT, window.getWindow());
    cube->start();
    ((Cube*)cube)->enableKeyInput();
    window.addGameObject(cube);



    glm::mat4 view;
    glm::mat4 projection;

    Shader* shader = cube->getShader();
    Camera* camera = new Camera(window.getWindow(), (float)WIDTH / (float)HEIGHT);
    camera->addShader(shader);
    camera->attachToGameObject(cube);
    // camera->enableCameraFilightControls();
    while (!window.shouldClose()) 
    {
        if (glfwGetKey(window.getWindow(), GLFW_KEY_C)) {
            camera->detachFromGameObject();
        }
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // unsigned int VBO, VAO;
        // glGenVertexArrays(1, &VAO);
        // glGenBuffers(1, &VBO);
        
        // float verticies[] = {
        //     cube->getPosition().x, cube->getPosition().y, cube->getPosition().z,
        //     cube->getPosition().x + cube->getFront().x, cube->getPosition().y + cube->getFront().y, cube->getPosition().z + cube->getFront().z,
        //     cube->getPosition().x, cube->getPosition().y, cube->getPosition().z,
        //     cube->getPosition().x + cube->getUp().x, cube->getPosition().y + cube->getUp().y, cube->getPosition().z + cube->getUp().z,
        //     cube->getPosition().x, cube->getPosition().y, cube->getPosition().z,
        //     cube->getPosition().x + cube->getRight().x, cube->getPosition().y + cube->getRight().y, cube->getPosition().z + cube->getRight().z,
        // };

        // glBindVertexArray(VAO);
        // glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
        
        // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        // glEnableVertexAttribArray(0);
        // shader->use();
        // glDrawArrays(GL_LINE, 0, 3);
        // glBindVertexArray(0);
        camera->update(deltaTime);
        window.update(deltaTime);
    }

    shader->deleteProgram();
    return EXIT_SUCCESS;
}