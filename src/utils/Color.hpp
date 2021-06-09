#ifndef COLOR
#define COLOR

class Color
{
private:
    int r; //value between 0 and 255
    int g;
    int b;
    int a;
    const int MAX_VALUE = 255;
public:
    Color();
    Color(int red, int green, int blue);
    Color(int red, int green, int blue, int alpha);
    Color(float red, float green, float blue);
    Color(float red, float green, float blue, float alpha);
    int getRedi();
    float getRedf();
    int getGreeni();
    float getGreenf();
    int getBluei();
    float getBluef();
    int getAlphai();
    float getAlphaf();
    void setRed(int red);
    void setRed(float red);
    void setGreen(int green);
    void setGreen(float green);
    void setBlue(int blue);
    void setBlue(float blue);
    void setAlpha(int alpha);
    void setAlpha(float alpha);
    ~Color();
};

#endif