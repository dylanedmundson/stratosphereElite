#include "GameObject.hpp"

unsigned int GameObject::ID_COUNTER = 0;
GameObject::GameObject()
{
    this->components = ArrayList<Component>();
    uid = ID_COUNTER;
    ID_COUNTER++;
}

GameObject::~GameObject()
{
    this->components.~ArrayList();
}

void GameObject::addComponent(Component c) {
    this->components.add(c);
}

Component GameObject::removeComponent(Component c) {
    return this->components.remove(c);
}

void GameObject::update(float dt) {
    int length = this->components.getSize();
    for (int i = 0; i < length; i++) {
        Component comp = this->components.get(i);
        comp.update(dt);
    }
}

void GameObject::start() {
    int length = this->components.getSize();
    for (int i = 0; i < length; i++) {
        Component comp = this->components.get(i);
        comp.start();
    }
}

bool GameObject::operator ==(GameObject rightHand) {
    return this->uid == rightHand.getUid();
}

int GameObject::getUid() {
    return this->uid;
}