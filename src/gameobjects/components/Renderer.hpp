#ifndef RENDERER
#define RENDERER
#include "Component.hpp"
#include "Texture.hpp"
#include "engine/Shader.hpp"
#include "utils/ArrayList.hpp"
class Renderer : public Component
{

    //TODO:================keep for texture abstraction int go
    // renderer->enableTexture();
    
    //upload and configure textures
    // Texture* texture1 = new Texture();
    // texture1->init("assets/wall.jpg", TEX_LINEAR, RGB);
    // Texture* texture2 = new Texture();
    // texture2->init("assets/awesomeface.png", TEX_LINEAR, RGBA);

    // renderer->addTexture(texture1);
    // renderer->addTexture(texture2);
    //================keep for texture abstraction int go

    //TODO: go add set alpha
    // renderer->setAlphaBlend(0.5f);
private:
    ArrayList<Texture*> textures;
    Shader* shader;
    unsigned int VBO, VAO;
    float* vertices;
    void render();
    bool hasColor;
    bool hasTex;
    GLenum usage;
    float alphaBlend;
    int sizeofVertices;
public:
    Renderer();
    Renderer(Shader* shader);
    void setShader(Shader* shader);
    void addTexture(Texture* tex);
    ~Renderer();
    void setVertices(float* vertices, int sizeofVertices);
    virtual void update(float dt);
    virtual void start();
    void enableColor();
    void enableTexture();
    void disableColor();
    void disableTexture();
    void setUsage(GLenum usage);
    void setAlphaBlend(float alpha);
    unsigned int getVAO();
};


#endif