// #include "utils/Shader.hpp"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
// #include <stb/stb_image.h>
// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
#include <engine/Window.hpp>
// void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main() {
    Window window = Window(800, 600, "stratosphereElite");
    window.init();

    float dt = 0.0;
    float lastFrame = glfwGetTime();

    while (!window.shouldClose())
    {
        float currentFrame = glfwGetTime();
        dt = currentFrame - lastFrame;
        lastFrame = currentFrame;
        window.update(dt);
    }

    glfwTerminate();
    return 0;
    
}