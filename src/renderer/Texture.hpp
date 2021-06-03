//TODO: handles all texture loading and parameter setting
#include <iostream>
#include <string.h>

enum TEX_TYPE {TEX_PIXEL, TEX_LINEAR};
enum IMG_FORMAT {RGB, RGBA};

class Texture
{
private:
    std::string filePath;
    unsigned int texID;
    int width, height;
public:
    void init(std::string filePath, TEX_TYPE type, IMG_FORMAT imgFormat);
    void bind();
    void unbind();
    int getWidth();
    int getHeight();
    unsigned int getID();
};