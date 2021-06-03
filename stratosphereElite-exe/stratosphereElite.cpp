// #include "utils/Shader.hpp"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
// #include <stb/stb_image.h>
// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
#include "engine/Window.hpp"
#include "renderer/Texture.hpp"
#include "renderer/Shader.hpp"
// void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main() {
    float dt = 0.0;
    float lastFrame = glfwGetTime();

    Window window = Window(800, 600, "stratosphereElite");
    window.init();

    float vertices[] = {
        //position          //texCoord
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f, //top L
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, //top R
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, //bot L
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, //bot L
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, //bot R
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f  //top R
    };
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    Texture tex1 = Texture();
    tex1.init("assets/wall.jpg", TEX_LINEAR, RGB);
    Texture tex2 = Texture();
    tex2.init("assets/awesomeface.png", TEX_LINEAR, RGBA);
    
    

    Shader shader = Shader();
    shader.loadShaderSource("shaders/vertex.glsl", GL_VERTEX_SHADER);
    shader.loadShaderSource("shaders/fragment.glsl", GL_FRAGMENT_SHADER);
    shader.compileAndLink();
    shader.use();
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);

    while (!window.shouldClose())
    {
        //TODO: texture abstraction done, now need to create some primitive objects
        //such as a sphere, cube etc, and use textures to be able to fill wals of 3D objects
        float currentFrame = glfwGetTime();
        dt = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        tex1.bind();
        glActiveTexture(GL_TEXTURE1);
        tex2.bind();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        // window.update(dt);
        
        window.swapAndPoll();
    }

    shader.deleteProgram();
    shader.~Shader();
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
    
}