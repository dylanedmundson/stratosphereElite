//TODO: abstract class for all components to extend
//gameobjects represent a single object like a player and contain many
//components such as a gun component, team component, render component,
//health component etc

//ref: https://www.raywenderlich.com/2806-introduction-to-component-based-architecture-in-games
#ifndef COMPONENT
#define COMPONENT
#include <iostream>
#include <string.h>

class Component
{
private:
    int uid;
    static unsigned int ID_COUNTER;
    std::string name;
public:
    //constants used for getting components by name
    static const char* RENDERER_NAME;
    static const char* TEXTURE_NAME;

    //functions
    Component();
    int getUid();
    ~Component();
    virtual void update(float dt);
    virtual void start();
    void setName(std::string newName);
    std::string getName();
    bool operator ==(Component right);
};
#endif