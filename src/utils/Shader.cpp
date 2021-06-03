#include "Shader.hpp"
#include "Shader.hpp"
#include <iostream>

using namespace std;

const int DEFAULT_SIZE = 10;
string rootDir = "../../";

void Shader::resize() {
    shaderSrc* newSources = new shaderSrc[this->maxSize * 10];
    for (int i = 0; i < this->size; i++) {
        newSources[i] = this->sources[i];
    }
    // shaderSrc* tmp = sources;
    delete[] this->sources;
    this->sources = newSources;
    newSources = nullptr;
    // delete[] tmp;
    // tmp = nullptr;
    this->maxSize = this->maxSize * 10;
}

Shader::Shader()
{
    this->sources = new shaderSrc[DEFAULT_SIZE];
    this->size = 0;
    this->maxSize = DEFAULT_SIZE;
}

Shader::~Shader()
{
    // segmentation fault with having this line in destructor on linux OS
    // move glDeleteProgram to its own function call
    // glDeleteProgram(this->shaderProgramID);
    delete[] sources;
    sources = nullptr;
}


void Shader::loadShaderSource(string path, GLenum shaderType) {
    if (this->size >= this->maxSize) {
        resize();
    }
    
    string filePath = rootDir + path;
    const char* filePathc = filePath.c_str();
    FILE *fileptr;
    long filelen;
    shaderSrc src;
    src.shaderType = shaderType;

    // open file and find file length
    fileptr = fopen(filePathc, "rb");
    fseek(fileptr, 0, SEEK_END);
    filelen = ftell(fileptr);
    rewind(fileptr);

     // read data into buffer
    src.shaderSource = new char[(filelen) * sizeof(char)];
    fread(src.shaderSource, filelen, sizeof(char), fileptr);
    fclose(fileptr);
    src.shaderSource[filelen] = '\0';

    this->sources[this->size] = src;
    this->size++;
}

void Shader::compileAndLink() {
    unsigned int shaderList[this->size];
    for (int i = 0; i < this->size; i++) {
        unsigned int shader;
        //create shader and compile
        shader = glCreateShader(this->sources[i].shaderType);
        glShaderSource(shader, 1, &this->sources[i].shaderSource, NULL);
        glCompileShader(shader);

        //check for compilation errors
        if (!printShaderError(this->sources[i].shaderType, shader)) {
            return;
        }
        shaderList[i] = shader;
    }

    //create program and link shaders
    this->shaderProgramID = glCreateProgram();
    for (int i = 0; i < this->size; i++) {
        glAttachShader(this->shaderProgramID, shaderList[i]);
    }
    glLinkProgram(this->shaderProgramID);

    //check to see if linking was successful
    int success;
    char infoLog[512];
    glGetProgramiv(this->shaderProgramID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->shaderProgramID, 512, NULL, infoLog);
        cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << endl <<
                infoLog << endl;
        return;
    } else {
        cout << "SHADER::PROGRAM::LINKING_SUCCESS" << endl;
    }

    for (int i = 0; i < this->size; i++) {
        glDeleteShader(shaderList[i]);
    }
}

void Shader::use() {
    glUseProgram(this->shaderProgramID);
}

void Shader::deleteProgram() {
    glDeleteProgram(this->shaderProgramID);
}

void Shader::setBool(const string &name, bool value) {
    int location = glGetUniformLocation(this->shaderProgramID, name.c_str());
    glUniform1i(location, (int) value); 
}

void Shader::setInt(const string &name, int value) {
    int location = glGetUniformLocation(this->shaderProgramID, name.c_str());
    glUniform1i(location, value);
}

void Shader::setFloat(const string &name, float value) {
    int location = glGetUniformLocation(this->shaderProgramID, name.c_str());
    glUniform1f(location, value);
}

void Shader::setVec3(const string &name, float v0, float v1, float v2) {
    int location = glGetUniformLocation(this->shaderProgramID, name.c_str());
    glUniform3f(location, v0, v1, v2);
}

void Shader::setVec4(const string &name, float v0, float v1, float v2, float v3) {
    int location = glGetUniformLocation(this->shaderProgramID, name.c_str());
    glUniform4f(location, v0, v1, v2, v3);
}

void Shader::setMat4(const std::string &name, glm::mat4 matrix) {
    int location = glGetUniformLocation(this->shaderProgramID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

bool Shader::printShaderError(GLenum type, int shader) {
    const char* shaderType;
    if (type == GL_VERTEX_SHADER) {
        shaderType = "VERTEX";
    } else if (type == GL_FRAGMENT_SHADER) {
        shaderType = "FRAGMENT";
    } else {
        shaderType = "UNDEFINED";
    }
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    char infoLog[512];
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        cout << "ERROR::SHADER::" << shaderType << "::COMPILATION_FAILED" << endl <<
                        infoLog << endl;
        return false;
    } else {
        cout << "COMPILATION::SUCCESS::" << shaderType << endl;
        return true;
    }
}