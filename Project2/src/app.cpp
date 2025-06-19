#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "renderer.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Polygon.h"


int main() {
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    GLFWwindow* window = glfwCreateWindow(640, 640, "Hello Circle", nullptr, nullptr);
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



    std::vector<float> positions;
    std::vector<unsigned int> indices;

    int segments = 4;

    Polygon::GenerateCircle(0.0f, 0.0f, 0.5f, segments, positions, indices);


    VertexArray va;
    VertexBuffer vb(positions.data(), positions.size() * sizeof(float));
    VertexBufferLayout layout;
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices.data(), indices.size());


    Shader shader("./res/shaders/vertex.shader", "./res/shaders/fragment.shader");
    shader.Bind();


    float r = 1.0f;
    float d = 0.01f;

    while (!glfwWindowShouldClose(window)) {
        GLCALL(glClear(GL_COLOR_BUFFER_BIT));

        shader.SetUniform4f("u_color", r, 0.0f, 0.5f, 1.0f);

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
