#include "utils/Shader.hpp"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <engine/Window.hpp>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;
const char* TITLE = "LearnOpenGL";

int main() {

    Window window(WIDTH, HEIGHT, TITLE);
    glfwSetFramebufferSizeCallback(window.getWindow(), framebuffer_size_callback);
    
    while (!window.shouldClose())
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        window.swapAndPoll();
    }
    
    return EXIT_SUCCESS;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
};