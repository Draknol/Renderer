#version 330 core

struct Material {
    sampler2D diffuse1;
    sampler2D specular1;
    vec3 ambient;
    float shininess;
};

struct DirectionalLight {
    vec3 direction;
    vec3 color;
};

struct PointLight {
    vec3 position;
    vec3 color;

    float constant;
    float linear;
    float quadratic;
};

struct Spotlight {
    vec3 position;
    vec3 direction;
    vec3 color;

    float cutOff;
    float constant;
    float linear;
    float quadratic;
};

const uint POINTLIGHTCOUNT = 4u;
const uint SPOTLIGHTCOUNT = 4u;

uniform Material material;
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[POINTLIGHTCOUNT];
uniform Spotlight spotlights[SPOTLIGHTCOUNT];
uniform vec3 viewPos;

in vec3 FragPos;
in vec2 TexCoord;
in vec3 Normal;

out vec4 FragColor;

vec3 calcDirLight(DirectionalLight light, vec3 norm, vec3 viewDir);
vec3 calcPointLight(PointLight light, vec3 norm, vec3 viewDir);
vec3 calcSpotLight(Spotlight light);

void main() {
    
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 lighting = 0 * calcDirLight(directionalLight, norm, viewDir);

    for (uint i = 0u; i < POINTLIGHTCOUNT; i++) {
        lighting += calcPointLight(pointLights[i], norm, viewDir);
    }

    for (uint i = 0u; i < SPOTLIGHTCOUNT; i++) {
        lighting += calcSpotLight(spotlights[i]);
    }

    FragColor = vec4(lighting, 1.0);
}

vec3 calcDirLight(DirectionalLight light, vec3 norm, vec3 viewDir) {

    // Ambient
    vec3 ambient = material.ambient;

    // Diffuse
    vec3 lightDir = normalize(-light.direction);
    vec3 diffuse = max(dot(norm, lightDir), 0.0) * light.color;

    // Specular
    vec3 reflectDir = reflect(-lightDir, norm);
    float shininess = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = texture(material.specular1, TexCoord).rgb * shininess;

    return texture(material.diffuse1, TexCoord).rgb * (ambient + diffuse + specular);
}

vec3 calcPointLight(PointLight light, vec3 norm, vec3 viewDir) {

    // Attenuation
    float dist = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * dist * dist);

    // Ambient
    vec3 ambient = material.ambient * attenuation;

    // Diffuse
    vec3 lightDir = normalize(light.position - FragPos);
    vec3 diffuse = max(dot(norm, lightDir), 0.0) * light.color * attenuation;

    // Specular
    vec3 reflectDir = reflect(-lightDir, norm);
    float shininess = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = texture(material.specular1, TexCoord).rgb * shininess * attenuation;

    return texture(material.diffuse1, TexCoord).rgb * (ambient + diffuse + specular);
}

vec3 calcSpotLight(Spotlight light) {
    // Theta
    vec3 lightDir = normalize(light.position - FragPos);
    float theta = dot(lightDir, normalize(-light.direction));

    // Attenuation
    float dist = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * dist * dist);

    // Ambient
    vec3 ambientColor = vec3(1.0);
    vec3 ambient = material.ambient * ambientColor * attenuation;

    if(theta > light.cutOff) {
        // Diffuse
        vec3 norm = normalize(Normal);
        vec3 diffuse = max(dot(norm, lightDir), 0.0) * light.color * attenuation;

        // Specular
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float shininess = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = texture(material.specular1, TexCoord).rgb * shininess * attenuation;

        return texture(material.diffuse1, TexCoord).rgb * (ambient + diffuse + specular);
    }
    else  {
        return ambient * texture(material.diffuse1, TexCoord).rgb;
    }
}