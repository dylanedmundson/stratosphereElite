#ifndef CUBE
#define CUBE
#include "utils/Color.hpp"
#include "glm/glm.hpp"
#include "gameobjects/GameObject.hpp"
#include "engine/Shader.hpp"
#include "gameobjects/components/Texture.hpp"
#include "utils/ArrayList.hpp"
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
    bool yawIsDirty = false;
    bool pitchIsDirty = false;
    bool rollIsDirty = false;
    GLFWwindow* window;
    Color* c;
    glm::mat4 translate;
    virtual void generateRenderer();
    void processKeyInput(float dt);
    void updateVectors();
public:
    Cube(Color* color, int width, int height, int depth, int windowWidth, int windowHeight, GLFWwindow* window);
    void setWidth(int width);
    void setHeight(int height);
    void setDepth(int depth);
    void setWindowWidth(int winWidth);
    void setWindowHeight(int winHeight);
    void setPos(glm::vec3 pos);
    void rollRot(float roll);
    void yawRot(float yawRot);
    void pitchRot(float pitchRot);
    void transform(glm::vec3 translate, float roll, float yaw, float pitch);
    void enableKeyInput();
    virtual void update(float dt);
    virtual void start();
    void setWindow(GLFWwindow* window);
    void addTexture(Texture* tex);
    ~Cube();
};

#endif