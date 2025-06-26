#version 330 core

struct Material {
    sampler2D diffuse1;
    sampler2D specular1;
    vec3 ambient;
    float shininess;
};

uniform Material material;
uniform vec3 lightPos;
uniform vec3 viewPos;

in vec3 FragPos;
in vec2 TexCoord;
in vec3 Normal;

out vec4 FragColor;

void main() {

    // Ambient
    vec3 lightColor = vec3(1.0);
    vec3 ambient = material.ambient * lightColor;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 diffuse = max(dot(norm, lightDir), 0.0) * lightColor;

    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float shininess = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = texture(material.specular1, TexCoord).rgb * shininess;

    FragColor = texture(material.diffuse1, TexCoord) * vec4(ambient + diffuse + specular, 1.0);
}