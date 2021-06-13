#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
uniform bool hasTex;
uniform sampler2D texture1;

void main() {
    if (hasTex) {
        FragColor = texture(texture1, TexCoord);
    } else {
        FragColor = vec4(ourColor, 1.0f);
    }
}