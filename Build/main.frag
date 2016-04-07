#version 330 core

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in mat4 Model;

uniform vec3 playerPos;

out vec4 color;

uniform sampler2D ourTexture;

void main()
{
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 lightPos = vec3(1.0, 0.5, 1.0);
    vec3 objectColor = vec3(1.0, 1.0, 1.0);

    // Ambient
    float ambientStrength = 0.3f;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular
    float specularStrength = 1.0f;
    vec3 viewDir = normalize(playerPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    color = vec4(result, 1.0f) * texture(ourTexture, TexCoord);
}