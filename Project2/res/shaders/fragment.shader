#version 330 core

in vec3 FragPos;
in vec3 Normal;

uniform vec3 u_lightPos;
uniform vec4 u_color;

out vec4 FragColor;

void main() {
    vec3 lightColor = vec3(1.0);
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(u_lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    
    vec3 diffuse = diff * lightColor;
    vec3 result = diffuse * vec3(u_color);
    FragColor = vec4(result, u_color.a);
}
