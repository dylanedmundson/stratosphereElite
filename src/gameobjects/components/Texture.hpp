#ifndef TEXTURE
#define TEXTURE
#include "gameobjects/components/Component.hpp"
#include <iostream>
#include <string.h>

enum TEX_TYPE {TEX_PIXEL, TEX_LINEAR};
enum IMG_FORMAT {RGB, RGBA};

class Texture : public Component
{
private:
    std::string filePath;
    unsigned int texID;
    int width, height;
    float fitVal;
public:
    void init(std::string filePath, TEX_TYPE type, IMG_FORMAT imgFormat);
    void bind();
    void unbind();
    int getWidth();
    int getHeight();
    void update(float dt);
    void setFitVal(float val);
    float getFitVal();
    void start();
    unsigned int getID();
    std::string getName();
    void blend(Texture* tex, float alpha);
};
#endif