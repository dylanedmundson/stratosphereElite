#ifndef GAME_OBJECT
#define GAME_OBJECT

#include "utils/ArrayList.hpp"
#include <iostream>
#include <string.h>
#include <glm/glm.hpp>
#include "gameobjects/components/Component.hpp"
#include "gameobjects/components/Renderer.hpp"

//FIXME: Gameobject will contain pointers to all possible components
//and each compoenent will be switch on and off using a boolean value

//alternatively figure out a way to allow component to access GameObject methods

class GameObject
{
protected:
    ArrayList<Component*>* components; //holds all components
    glm::vec3 position; //needed for objects position
    glm::vec3 objFront;
    glm::vec3 objUp;
    glm::vec3 objRight;
    glm::mat4 model;
    Renderer* renderer; //needed for rendering
    Shader* shader; // needed for changes to matirces
    virtual void generateRenderer();
    virtual void generateShader();
    float yaw;
    float pitch;
    float roll;
    float prevYaw;
    float prevPitch;
    float prevRoll;
private:
    int uid;
    static unsigned int ID_COUNTER;
public:
    GameObject();
    ~GameObject();
    void addComponent(Component* c);
    Component* removeComponent(Component* c);
    ArrayList<Component*>* getAllComponents();
    Component* getComponent(std::string);
    bool operator ==(GameObject rightHand);
    int getUid();
    Renderer* getRenderer();
    Shader* getShader();
    glm::vec3 getPosition();
    glm::vec3 getFront();
    glm::vec3 getUp();
    glm::vec3 getRight();

    virtual void update(float dt);
    virtual void start();
};

#endif