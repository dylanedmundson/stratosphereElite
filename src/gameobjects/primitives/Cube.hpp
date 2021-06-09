#ifndef CUBE
#define CUBE
#include "utils/Color.hpp"
#include "glm/glm.hpp"
#include "gameobjects/GameObject.hpp"
#include "engine/Shader.hpp"

class Cube : public GameObject
{
protected:
    int width;
    int height;
    int depth;
    int windowWidth;
    int windowHeight;
    Color* c;
    virtual void generateRenderer();
    virtual void generateShader();
public:
    Cube();
    Cube(Color* color, int width, int height, int depth, int windowWidth, int windowHeight);
    void setWidth(int width);
    void setHeight(int height);
    void setDepth(int depth);
    void setWindowWidth(int winWidth);
    void setWindowHeight(int winHeight);
    void setPos(glm::vec3 pos);
    virtual void update(float dt);
    virtual void start();
    ~Cube();
};

#endif