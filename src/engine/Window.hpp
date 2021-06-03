#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

class Window
{
private:
    GLFWwindow* window;
    void framebuffer_size_callback(GLFWwindow *window, int width, int height);
public:
    Window(int width, int height, const char* title);
    GLFWwindow* getWindow();
    bool shouldClose();
    void swapAndPoll();
    ~Window();
};

Window::Window(int width, int height, const char* title)
{
    //window initialization
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    //create window object
    this->window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (this->window == NULL) {
        //error if failed to create window
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    //TODO: figure out how to work around this problem
    // callback &callbacks = callback::getInstance();
    // glfwSetFramebufferSizeCallback(this->window, &callback::framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl; 
    }
}

Window::~Window()
{
    glfwTerminate();
}

GLFWwindow* Window::getWindow() {
    return this->window;
}

bool Window::shouldClose() {
    return glfwWindowShouldClose;
}

void Window::swapAndPoll() {
    glfwSwapBuffers(this->window);
    glfwPollEvents();
}