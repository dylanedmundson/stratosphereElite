#ifndef WINDOW
#define WINDOW
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "WindowCallbacks.hpp"
#include "utils/ArrayList.hpp"
#include "gameobjects/GameObject.hpp"
#include "engine/Camera.hpp"

class Window
{
private:
    GLFWwindow* window;
    int width;
    int height;
    const char* title;
    ArrayList<GameObject*>* gameObjects;
    void processCameraKeyInput();
    void processWindowKeyInputs();
public:
    Window(int width, int height, const char* title);
    GLFWwindow* getWindow();
    bool shouldClose();
    void init();
    void swapAndPoll();
    void update(float dt);
    void addGameObject(GameObject* go);
    int getWidth();
    int getHeight();
    ~Window();
};
#endif