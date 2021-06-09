#include "Component.hpp"

unsigned int Component::ID_COUNTER = 0;
const char* Component::RENDERER_NAME = "renderer";
const char* Component::TEXTURE_NAME = "texture";

Component::Component()
{
    this->uid = this->ID_COUNTER;
    this->ID_COUNTER++;
}

Component::~Component()
{
}

int Component::getUid() {
    return uid;
}

bool Component::operator ==(Component right) {
    return this->uid == right.getUid();
}

void Component::update(float dt) {

}

void Component::start() {
    
}

void Component::setName(std::string newName) {
    this->name = newName;
}

std::string Component::getName() {
    return this->name;
}