#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in mat4 worldTransform;

uniform mat4 projView;
uniform mat4 localTransform;

out vec3 FragPos;
out vec2 TexCoord;
out vec3 Normal;

void main() {
    mat4 modelTransform = worldTransform * localTransform;
    vec4 modelPos = modelTransform * vec4(aPos, 1.0);
    
    gl_Position = projView * modelPos;

    FragPos = vec3(modelPos);

    TexCoord = aTexCoord;

    Normal = mat3(transpose(inverse(modelTransform))) * aNormal;
}