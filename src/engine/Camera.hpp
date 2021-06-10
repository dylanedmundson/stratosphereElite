#ifndef CAMERA
#define CAMERA
#include <glm/glm.hpp>
#include "Shader.hpp"
#include <GLFW/glfw3.h>
#include "utils/ArrayList.hpp"

class Camera
{
private:
    const float speed = 2.5f;
    const float rotSpeed = 2.5f;
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    ArrayList<Shader*>* shaders;
    GLFWwindow* window;
    void processKeyInput(float dt);
    bool flightControlsEnabled;
    glm::mat4 projection;
    float aspectRatio;

public:
    Camera(GLFWwindow* window, float aspectRatio);
    glm::vec3 getCameraPos();
    glm::vec3 getCameraFront();
    glm::vec3 getCameraUp();
    void setCameraPos(glm::vec3 vec);
    void setCameraUp(glm::vec3 vec);
    void setCamerFront(glm::vec3 vec);
    void addShader(Shader* shader);
    void update(float dt);
    void enableCameraFilightControls();
    void disableCameraControls();
    void setAspectRatio(float apectRatio);
    bool controlsEnabled();
    ~Camera();
};


#endif