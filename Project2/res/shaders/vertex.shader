#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
    FragPos = vec3(model * vec4(a_Position, 1.0));
    Normal = mat3(transpose(inverse(model))) * a_Normal;

    gl_Position = proj * view * vec4(FragPos, 1.0);
}
