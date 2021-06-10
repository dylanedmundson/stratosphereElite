#include "engine/Shader.hpp"
#include "ArrayList.hpp"
#include <iostream>
#include <string>

class AssetPool
{
private:
    static ArrayList<Shader*>* shaders;
public:
    static Shader* getShader(std::string resourceName);
    ~AssetPool();
};