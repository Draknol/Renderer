#version 330 core

struct Material {
    sampler2D texture_diffuse1;
};

uniform Material material;
in vec2 TexCoord;
out vec4 FragColor;

void main() {
    FragColor = texture(material.texture_diffuse1, TexCoord);
}