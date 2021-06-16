#include "GameObject.hpp"
ArrayList<GameObject*>* GameObject::GAME_OBJECTS = new ArrayList<GameObject*>();
GameObject* GameObject::getGameObject(int uid) {
    int len = GameObject::GAME_OBJECTS->getSize();
    for (int i = 0; i < len; i++) {
        GameObject* go = GAME_OBJECTS->get(i);
        if (go->getUid() == uid) {
            return go;
        }
    }
    return nullptr;
}

unsigned int GameObject::ID_COUNTER = 0;
GameObject::GameObject()
{
    this->components = new ArrayList<Component*>();
    uid = ID_COUNTER;
    ID_COUNTER++;
    this->hasTex = false;
    GameObject::GAME_OBJECTS->add(this);
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
    c->setGo(this->uid);
    if (c->getName() == Component::TEXTURE_NAME) {
        this->hasTex = true;
    }
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

Component* GameObject::getComponent(std::string name) {
    int compLen = this->components->getSize();
    for (int i = 0; i < compLen; i++) {
        Component* comp = this->components->get(i);
        if (comp->getName() == name.c_str()) {
            return comp;
        }
    }
    return nullptr;
}