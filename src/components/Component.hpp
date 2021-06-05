//TODO: abstract class for all components to extend
//gameobjects represent a single object like a player and contain many
//components such as a gun component, team component, render component,
//health component etc

//ref: https://www.raywenderlich.com/2806-introduction-to-component-based-architecture-in-games
#pragma
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
    Component();
    int getUid();
    ~Component();
    virtual void update(float dt);
    virtual void start();
    virtual void setName(std::string newName);
    virtual std::string getName();
    bool operator ==(Component right);
};
#endif