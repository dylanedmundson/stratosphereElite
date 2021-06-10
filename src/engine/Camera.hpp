#ifndef CAMERA
#define CAMERA
#include <glm/glm.hpp>
#include "Shader.hpp"
#include <GLFW/glfw3.h>
#include "utils/ArrayList.hpp"

class Camera
{
private:
    // const float speed = 2.5f;
    // const float rotSpeed = 2.0f;
    // float yaw;
    // float pitch;
    // bool firstMouse;
    // float zoom;
    // float lastx;
    // float lasty;
    const float speed = 2.5f;
    const float rotSpeed = 2.5f;
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    ArrayList<Shader*>* shaders;
    GLFWwindow* window;
    void processKeyInput(float dt);

public:
    Camera(GLFWwindow* window);
    glm::vec3 getCameraPos();
    glm::vec3 getCameraFront();
    glm::vec3 getCameraUp();
    void setCameraPos(glm::vec3 vec);
    void setCameraUp(glm::vec3 vec);
    void setCamerFront(glm::vec3 vec);
    void addShader(Shader* shader);
    void update(float dt);
    ~Camera();
};


#endif