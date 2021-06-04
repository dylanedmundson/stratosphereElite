#include "Window.hpp"
Window::Window(int width, int height, const char* title)
{
    this->width = width;
    this->height = height;
    this->title = title;
}

void Window::init() {
    //window initialization
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    //create window object
    window = glfwCreateWindow(this->width, this->height, this->title, NULL, NULL);
    if (window == NULL) {
        //error if failed to create window
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

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
    return glfwWindowShouldClose(this->window);
}

void Window::swapAndPoll() {
    glfwSwapBuffers(this->window);
    glfwPollEvents();
}

void Window::update(float dt) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    int goLength = gameObjects.getSize();
    for (int i = 0; i < goLength; i++) {
        gameObjects.get(i).update(dt);
    }
    this->swapAndPoll();
}