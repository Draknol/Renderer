#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in mat4 worldTransform;

out vec2 TexCoord;

uniform mat4 projView;
uniform mat4 localTransform;

void main() {
    gl_Position = projView * worldTransform * localTransform * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}