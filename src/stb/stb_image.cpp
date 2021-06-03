#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <string>

const std::string rootDir = "../../";

unsigned char* my_stbi_load(char const *filename, int *x, int *y, int *channels_in_file, int desired_channels) {
    std::string dir = rootDir + filename;
    return stbi_load(dir.c_str(), x, y, channels_in_file, desired_channels);
}