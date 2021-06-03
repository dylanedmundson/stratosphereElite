#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "WindowCallbacks.hpp"

class Window
{
private:
    GLFWwindow* window;
    int width;
    int height;
    const char* title;
public:
    Window(int width, int height, const char* title);
    GLFWwindow* getWindow();
    bool shouldClose();
    void init();
    void swapAndPoll();
    void update(float dt);
    ~Window();
};