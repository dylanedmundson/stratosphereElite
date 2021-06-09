#include "Color.hpp"
#include <iostream>
#include <string.h>

Color::Color() {
}

Color::Color(int red, int green, int blue)
{
    if (red > MAX_VALUE || green > MAX_VALUE || blue > MAX_VALUE ||
    red < 0 || green < 0 || blue < 0) {
        std::string errMsg;
        errMsg = "invalid input, max value = 255 , min = 0";
        throw std::runtime_error(errMsg.c_str());
    }
    this->r = red;
    this->g = green;
    this->b = blue;
}

Color::Color(int red, int green, int blue, int alpha)
{
    if (red > MAX_VALUE || green > MAX_VALUE || blue > MAX_VALUE || alpha > MAX_VALUE ||
    red < 0 || green < 0 || blue < 0 || alpha < 0) {
        std::string errMsg;
        errMsg = "invalid input, max value = 255 , min = 0";
        throw std::runtime_error(errMsg.c_str());
    }
    this->r = red;
    this->g = green;
    this->b = blue;
    this->a = alpha;
}

Color::Color(float red, float green, float blue) {
    if (red > 1.0f|| green > 1.0f || blue > 1.0f ||
    red < 0.0f || green < 0.0f || blue < 0.0f) {
        std::string errMsg;
        errMsg = "invalid input, max value = 255 , min = 0";
        throw std::runtime_error(errMsg.c_str());
    }
    this->r = red * MAX_VALUE;
    this->g = green * MAX_VALUE;
    this->b = blue * MAX_VALUE;
}
Color::Color(float red, float green, float blue, float alpha) {
    if (red > 1.0f|| green > 1.0f || blue > 1.0f || alpha > 1.0f ||
    red < 0.0f || green < 0.0f || blue < 0.0f || alpha < 0.0f) {
        std::string errMsg;
        errMsg = "invalid input, max value = 255 , min = 0";
        throw std::runtime_error(errMsg.c_str());
    }
    this->r = red * MAX_VALUE;
    this->g = green * MAX_VALUE;
    this->b = blue * MAX_VALUE;
    this->a = alpha * MAX_VALUE;
}

Color::~Color()
{
}

int Color::getRedi() {
    return this->r;
}
float Color::getRedf() {
    return (float)this->r / (float)MAX_VALUE;
}
int Color::getGreeni() {
    return this->g;
}
float Color::getGreenf() {
    return (float)this->g / (float)MAX_VALUE;
}
int Color::getBluei() {
    return this->b;
}
float Color::getBluef() {
    return (float)this->b / (float)MAX_VALUE;
}
int Color::getAlphai() {
    return this->a;
}
float Color::getAlphaf() {
    return (float)this->a / (float)MAX_VALUE;
}

void Color::setRed(int red) {
    if (red > MAX_VALUE || red < 0) {
        std::string errMsg;
        errMsg = "invalid input, max value = 255 , min = 0";
        throw std::runtime_error(errMsg.c_str());
    }
    this->r = red;
}
void Color::setRed(float red) {
    if (red > 1.0f || red < 0.0f) {
        std::string errMsg;
        errMsg = "invalid input, max value = 255 , min = 0";
        throw std::runtime_error(errMsg.c_str());
    }
    this->r = red * MAX_VALUE;
}
void Color::setGreen(int green) {
    if (green > MAX_VALUE || green < 0) {
        std::string errMsg;
        errMsg = "invalid input, max value = 255 , min = 0";
        throw std::runtime_error(errMsg.c_str());
    }
    this->g = green;
}
void Color::setGreen(float green) {
    if (green > 1.0f || green < 0.0f) {
        std::string errMsg;
        errMsg = "invalid input, max value = 255 , min = 0";
        throw std::runtime_error(errMsg.c_str());
    }
    this->g = green * MAX_VALUE;
}
void Color::setBlue(int blue) {
    if (blue > MAX_VALUE || blue < 0) {
        std::string errMsg;
        errMsg = "invalid input, max value = 255 , min = 0";
        throw std::runtime_error(errMsg.c_str());
    }
    this->b = blue;
}
void Color::setBlue(float blue) {
    if (blue > 1.0f || blue < 0.0f) {
        std::string errMsg;
        errMsg = "invalid input, max value = 255 , min = 0";
        throw std::runtime_error(errMsg.c_str());
    }
    this->b = blue * MAX_VALUE;
}
void Color::setAlpha(int alpha) {
    if (alpha > MAX_VALUE || alpha < 0) {
        std::string errMsg;
        errMsg = "invalid input, max value = 255 , min = 0";
        throw std::runtime_error(errMsg.c_str());
    }
    this->a = alpha;
}
void Color::setAlpha(float alpha) {
    if (alpha > 1.0f || alpha < 0.0f) {
        std::string errMsg;
        errMsg = "invalid input, max value = 255 , min = 0";
        throw std::runtime_error(errMsg.c_str());
    }
    this->a = alpha * MAX_VALUE;
}