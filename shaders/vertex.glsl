#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;


out vec2 TexCoord;
uniform mat4 transform; //define unfiorm to hold transform info
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * transform * vec4(aPos, 1.0); // now we can multiply the vector by the transform to update its position
    TexCoord = aTexCoord;
}