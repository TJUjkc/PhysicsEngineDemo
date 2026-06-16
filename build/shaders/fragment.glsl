#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec3 Color;

uniform vec3 uLightPos;
uniform vec3 uLightColor;
uniform vec3 uAmbientColor;

out vec4 FragColor;

void main() {
    // 简单漫反射 + 环境光照明
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(uLightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);

    vec3 ambient = uAmbientColor * Color;
    vec3 diffuse = uLightColor * diff * Color;

    // 边缘光照，提高边缘可见度
    float rim = 1.0 - max(dot(norm, normalize(FragPos)), 0.0);
    vec3 rimColor = vec3(0.1, 0.1, 0.2) * pow(rim, 3.0);

    FragColor = vec4(ambient + diffuse + rimColor, 1.0);
}