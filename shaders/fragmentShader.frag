#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
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

const uint DIRECTIONALLIGHTCOUNT = 1u;
const uint POINTLIGHTCOUNT = 4u;
const uint SPOTLIGHTCOUNT = 4u;

uniform Material material;

uniform DirectionalLight directionalLights[DIRECTIONALLIGHTCOUNT];
uniform PointLight pointLights[POINTLIGHTCOUNT];
uniform Spotlight spotlights[SPOTLIGHTCOUNT];

uniform mat4 directionalProjViews[DIRECTIONALLIGHTCOUNT];
uniform mat4 spotProjViews[SPOTLIGHTCOUNT];

uniform sampler2DArray directionalShadowMaps;
uniform sampler2DArray spotShadowMaps;

uniform vec3 viewPos;

in vec4 FragPos;
in vec2 TexCoord;
in vec3 Normal;

vec4 DirectionalFragPos[DIRECTIONALLIGHTCOUNT];
vec4 SpotFragPos[SPOTLIGHTCOUNT];
vec3 fragPos;

out vec4 FragColor;

vec3 calcDirLights(vec3 norm, vec3 viewDir);
vec3 calcPointLights(vec3 norm, vec3 viewDir);
vec3 calcSpotLights(vec3 norm, vec3 viewDir);

float ShadowCalculation(vec4 lightFragPos, sampler2DArray shadowMaps, vec3 norm, vec3 lightDir, uint shadowMapsIndex);

void main() {

    for (uint i = 0u; i < DIRECTIONALLIGHTCOUNT; i++) {
        DirectionalFragPos[i] = directionalProjViews[i] * FragPos;
    }

    for (uint i = 0u; i < SPOTLIGHTCOUNT; i++) {
        SpotFragPos[i] = spotProjViews[i] * FragPos;
    }

    fragPos = FragPos.xyz;
    
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - fragPos);

    // Add directionals
    vec3 lighting = calcDirLights(norm, viewDir);

    // Add points
    lighting += calcPointLights(norm, viewDir);

    // Add spots
    lighting += calcSpotLights(norm, viewDir);

    FragColor = vec4(lighting, 1.0);
}

vec3 calcDirLights(vec3 norm, vec3 viewDir) {

    vec3 ambient = material.ambient * DIRECTIONALLIGHTCOUNT;
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);
    float shadow = DIRECTIONALLIGHTCOUNT;

    for (uint i = 0u; i < DIRECTIONALLIGHTCOUNT; i++) {
        DirectionalLight light = directionalLights[i];

        // Diffuse
        vec3 lightDir = normalize(-light.direction);
        diffuse += max(dot(norm, lightDir), 0.0) * light.color;

        // Specular
        vec3 halfwayDir = normalize(lightDir + viewDir);
        float shininess = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
        specular += shininess * light.color;

        // Shadow
        shadow -= ShadowCalculation(DirectionalFragPos[i], directionalShadowMaps, norm, lightDir, i);
    }
    
    return texture(material.diffuse, TexCoord).rgb * (ambient + shadow * (diffuse + (texture(material.specular, TexCoord).rgb * specular)));
}

vec3 calcPointLights(vec3 norm, vec3 viewDir) {

    vec3 ambient = DIRECTIONALLIGHTCOUNT * material.ambient;
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);

    for (uint i = 0u; i < POINTLIGHTCOUNT; ++i) {
        PointLight light = pointLights[i];

        // Attenuation
        vec3 lightDir = light.position - fragPos;
        float dist = length(lightDir);
        float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * dist * dist);

        // Diffuse
        lightDir = normalize(lightDir);
        diffuse += max(dot(norm, lightDir), 0.0) * light.color * attenuation;

        // Specular
        vec3 halfwayDir = normalize(lightDir + viewDir);
        float shininess = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
        specular += shininess * attenuation * light.color;
    }

    return texture(material.diffuse, TexCoord).rgb * (ambient + diffuse + (texture(material.specular, TexCoord).rgb * specular));
}

vec3 calcSpotLights(vec3 norm, vec3 viewDir) {
    vec3 ambient = DIRECTIONALLIGHTCOUNT * material.ambient;
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);
    float shadow = DIRECTIONALLIGHTCOUNT;

    for (uint i = 0u; i < SPOTLIGHTCOUNT; ++i) {
        Spotlight light = spotlights[i];

        // Theta
        vec3 lightDir = normalize(light.position - fragPos);
        float theta = dot(lightDir, normalize(-light.direction));

        if (theta > light.cutOff) {
            // Attenuation
            float dist = length(light.position - fragPos);
            float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * dist * dist);

            // Diffuse
            diffuse += max(dot(norm, lightDir), 0.0) * light.color * attenuation;

            // Specular
            vec3 halfwayDir = normalize(lightDir + viewDir);
            float shininess = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
            specular += shininess * attenuation * light.color;

            // Shadow
            shadow -= ShadowCalculation(SpotFragPos[i], spotShadowMaps, norm, lightDir, i);
        }
    }

    return texture(material.diffuse, TexCoord).rgb * (ambient + shadow * (diffuse + (texture(material.specular, TexCoord).rgb * specular)));
}

float ShadowCalculation(vec4 fragPosLightSpace, sampler2DArray shadowMaps, vec3 norm, vec3 lightDir, uint shadowMapsIndex) {

    // Projection
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;
    if(projCoords.z > 1.0) return 0.0;

    // Get depth of closest frag
    float closestDepth = texture(shadowMaps, vec3(projCoords.xy, shadowMapsIndex)).r; 
    
    // Get depth of current frag
    float currentDepth = projCoords.z;

    // Bias
    float bias = max(0.001 * (1.0 - dot(norm, lightDir)), 0.00005); 

    // PCF shadows
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMaps, 0).xy;
    for(float x = -1.0; x <= 1.0; x+=1.0) {
        for(float y = -1.0; y <= 1.0; y+=1.0) {
            float pcfDepth = texture(shadowMaps, vec3(projCoords.xy + vec2(x, y) * texelSize, shadowMapsIndex)).r; 
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;

    return shadow;
}