#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <glm/gtc/matrix_transform.hpp>

typedef struct shaderSrc
    {
        char* shaderSource;
        GLenum shaderType;
    } shaderSource;

class Shader
{
private:
    shaderSrc* sources;
    int size;
    int maxSize;
    unsigned int shaderProgramID;
    void resize();
    bool printShaderError(GLenum type, int shader);
public:
    Shader();
    ~Shader();
    void loadShaderSource(std::string path, GLenum shaderType);
    void compileAndLink();
    void use();
    void deleteProgram();
    void setBool(const std::string &name, bool value);
    void setInt(const std::string &name, int value);
    void setFloat(const std::string &name, float value);
    void setVec4(const std::string &name, float v0, float v1, float v2, float v3);
    void setVec3(const std::string &name, float v0, float v1, float v2);
    void setMat4(const std::string &name, glm::mat4 matrix);
};

#endif