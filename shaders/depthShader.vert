#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 3) in mat4 worldTransform;

uniform mat4 lightProjView;
uniform mat4 localTransform;

void main() {
    gl_Position = lightProjView * worldTransform * localTransform * vec4(aPos, 1.0);
}