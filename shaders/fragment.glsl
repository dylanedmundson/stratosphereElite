#version 330 core
out vec4 FragColor;

// in vec4 vertexColor; //input variable from vs (same name and type)
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1; //assign our texture object to this uniform
uniform sampler2D texture2;
uniform float alphaBlend;

void main() {
    FragColor = mix(
        texture(texture1, TexCoord),
        texture(texture2, TexCoord), alphaBlend
    );
}