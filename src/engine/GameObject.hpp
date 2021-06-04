#ifndef GAME_OBJECT
#define GAME_OBJECT

#include "utils/List.hpp"
#include "utils/ArrayList.hpp"
#include "components/Component.hpp"
#include <iostream>

class GameObject
{
private:
    ArrayList<Component> components;
    int uid;
    static unsigned int ID_COUNTER;
public:
    GameObject();
    ~GameObject();
    void addComponent(Component c);
    Component removeComponent(Component c);
    void update(float dt);
    void start();
    ArrayList<Component> getAllComponents();
    bool operator ==(GameObject rightHand);
    int getUid();
};
#endif