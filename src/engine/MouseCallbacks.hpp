#ifndef MOUSECALLBACKS
#define MOUSECALLBACKS

#include <GLFW/glfw3.h>
static float lastX = 400, lastY = 300; //initail mouse position, initiallized to center screen
static float yaw = -90.0f; // to make sure point in - z dir yaw gets 90 degree rotation
static float pitch = 0.0f;
static bool firstMouse = true;
static float zoom = 45.0f;

static void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    //calculate change in mouse poisition since last callback
    float xOffset = xpos - lastX;
    float yOffset = lastY - ypos; //reversed: y ranges bottom to top
    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.1f;
    xOffset *= sensitivity; //multiply offset by mouse sensitivity
    yOffset *= sensitivity;

    //add these values to the pitch and yaw values
    yaw += xOffset;
    pitch += yOffset;

    //lastly we need to constrain the users to only be able to look up -89 degrees above that we get LookAt flip which causes
    //some weird interfacial issues, we just replace euler value with its constraint
    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    if (pitch < -89.0f) {
        pitch = -89.0f;
    }
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    zoom -= (float) yoffset;
    if (zoom < 1.0f) {
        zoom =  1.0f;
    }
    if (zoom > 45) {
        zoom = 45.0f;
    }
}

#endif