#include "AssetPool.hpp"
#include "glad/glad.h"

ArrayList<Shader*>* AssetPool::shaders = new ArrayList<Shader*>();

Shader* AssetPool::getShader(std::string resourceName) {
    int len = AssetPool::shaders->getSize();
    for (int i = 0; i < len; i++) {
        if (AssetPool::shaders->get(i)->getShaderName() == resourceName) {
            return AssetPool::shaders->get(i);
        }
    }
    Shader* shader = new Shader();
    shader->loadShaderSource(resourceName + "/vertex.glsl", GL_VERTEX_SHADER);
    shader->loadShaderSource(resourceName + "/fragment.glsl", GL_FRAGMENT_SHADER);
    shader->compileAndLink();
    shader->setShaderName(resourceName);
    AssetPool::shaders->add(shader);
    return shader;
}

AssetPool::~AssetPool() {
    delete AssetPool::shaders;
    AssetPool::shaders = nullptr;
}