#ifndef CUBE
#define CUBE
#include "utils/Color.hpp"
#include "glm/glm.hpp"
#include "gameobjects/GameObject.hpp"
#include "engine/Shader.hpp"
#include <GLFW/glfw3.h>

class Cube : public GameObject
{
protected:
    const float speed = 2.5f;
    const float rotSpeed = 120.0f;
    int width;
    int height;
    int depth;
    int windowWidth;
    int windowHeight;
    bool keyInputEnabled;
    GLFWwindow* window;
    Color* c;
    virtual void generateRenderer();
    virtual void generateShader();
    void processKeyInput(float dt);
public:
    Cube();
    Cube(Color* color, int width, int height, int depth, int windowWidth, int windowHeight, GLFWwindow* window);
    void setWidth(int width);
    void setHeight(int height);
    void setDepth(int depth);
    void setWindowWidth(int winWidth);
    void setWindowHeight(int winHeight);
    void setPos(glm::vec3 pos);
    void enableKeyInput();
    virtual void update(float dt);
    virtual void start();
    void setWindow(GLFWwindow* window);
    ~Cube();
};

#endif