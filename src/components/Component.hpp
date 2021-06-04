//TODO: abstract class for all components to extend
//gameobjects represent a single object like a player and contain many
//components such as a gun component, team component, render component,
//health component etc

//ref: https://www.raywenderlich.com/2806-introduction-to-component-based-architecture-in-games
#pragma
#ifndef COMPONENT
#define COMPONENT

class Component
{
private:
    int uid;
    static unsigned int ID_COUNTER;
public:
    Component();
    int getUid();
    ~Component();
    virtual void update(float dt);
    virtual void start();
    bool operator ==(Component right);
};
#endif