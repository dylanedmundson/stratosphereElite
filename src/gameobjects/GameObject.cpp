#include "GameObject.hpp"

unsigned int GameObject::ID_COUNTER = 0;
GameObject::GameObject()
{
    this->components = new ArrayList<Component*>();
    uid = ID_COUNTER;
    ID_COUNTER++;
}

GameObject::~GameObject()
{
    delete this->components;
    components = nullptr;
    delete this->renderer;
    renderer = nullptr;
    delete this->shader;
    shader = nullptr;
}

void GameObject::addComponent(Component* c) {
    this->components->add(c);
}

Component* GameObject::removeComponent(Component* c) {
    return this->components->remove(c);
}

void GameObject::update(float dt) {
    int length = this->components->getSize();
    for (int i = 0; i < length; i++) {
        Component* comp = this->components->get(i);
        (*comp).update(dt);
    }
}

void GameObject::start() {
    int length = this->components->getSize();
    for (int i = 0; i < length; i++) {
        Component* comp = this->components->get(i);
        (*comp).start();
    }
}

bool GameObject::operator ==(GameObject rightHand) {
    return this->uid == rightHand.getUid();
}

int GameObject::getUid() {
    return this->uid;
}

Component* GameObject::getComponent(std::string name) {
    int len = this->components->getSize();
    for (int i = 0; i < len; i++) {
        if (this->components->get(i)->getName() == name.c_str()) {
            return this->components->get(i);
        }
    }
    return nullptr;
}

ArrayList<Component*>* GameObject::getAllComponents() {
    return this->components;
}

Renderer* GameObject::getRenderer() {
    return this->renderer;
}

Shader* GameObject::getShader() {
    return this->shader;
}

void GameObject::generateRenderer() {

}

void GameObject::generateShader() {

}

glm::vec3 GameObject::getPosition() {
    return this->position;
}

glm::vec3 GameObject::getFront() {
    return this->objFront;
}

glm::vec3 GameObject::getUp() {
    return this->objUp;
}

glm::vec3 GameObject::getRight() {
    return this->objRight;
}