#ifndef RENDERER
#define RENDERER
#include "Component.hpp"
#include "Texture.hpp"
#include "engine/Shader.hpp"
#include "utils/ArrayList.hpp"
class Renderer : public Component
{
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