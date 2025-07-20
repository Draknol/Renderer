#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in mat4 aWorldTransform;

uniform mat4 projView;
uniform mat4 localTransform;

out vec4 FragPos;
out vec2 TexCoord;
out vec3 Normal;


void main() {
    mat4 modelTransform = aWorldTransform * localTransform;

    FragPos = modelTransform * vec4(aPos, 1.0);
    
    gl_Position = projView * FragPos;

    TexCoord = aTexCoord;

    Normal = transpose(inverse(mat3(modelTransform))) * aNormal;
}