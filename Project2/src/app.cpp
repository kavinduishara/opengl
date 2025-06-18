#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

#include "renderer.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "Shader.h"

#define _USE_MATH_DEFINES
const float PI = 3.14159265359f;

int main() {
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello Circle", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    const int segments = 10;
    float positions[(segments + 2) * 2];
    unsigned int indices[segments * 3];

    float centerX = 0.0f, centerY = 0.0f, radius = 0.5f;
    positions[0] = centerX;
    positions[1] = centerY;

    for (int i = 0; i <= segments; ++i) {
        float angle = 2.0f * PI * i / segments;
        positions[(i + 1) * 2 + 0] = centerX + std::cos(angle) * radius;
        positions[(i + 1) * 2 + 1] = centerY + std::sin(angle) * radius;
    }

    for (int i = 0; i < segments; ++i) {
        indices[i * 3 + 0] = 0;
        indices[i * 3 + 1] = i + 1;
        indices[i * 3 + 2] = (i + 2 > segments) ? 1 : i + 2;
    }

    unsigned int vao;
    GLCALL(glGenVertexArrays(1, &vao));
    GLCALL(glBindVertexArray(vao));

    VertexBuffer vb(positions, sizeof(positions));
    IndexBuffer ib(indices, segments * 3);

    GLCALL(glEnableVertexAttribArray(0));
    GLCALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));


    Shader shader("./res/shaders/vertex.shader", "./res/shaders/fragment.shader");
    shader.Bind();


    float r = 1.0f;
    float d = 0.01f;

    while (!glfwWindowShouldClose(window)) {
        GLCALL(glClear(GL_COLOR_BUFFER_BIT));

        shader.SetUniform4f("u_color", r, 0.0f, 0.5f, 1.0f);

        //ib.Bind();
        GLCALL(glDrawElements(GL_TRIANGLES, segments * 3, GL_UNSIGNED_INT, nullptr));

        r += d;
        if (r > 1.0f || r < 0.0f)
            d = -d;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
