#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1000, 1000, "Hello Circle", nullptr, nullptr);
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

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    /*std::vector<float> positions;
    std::vector<unsigned int> indices;*/

    std::vector<float> positions = {
        // position           // normal
         0.0f,  0.0f,  1.0f,   0.0f,  0.0f,  1.0f,  // top
         1.0f,  0.0f,  0.0f,   1.0f,  0.0f,  0.0f,  // right
        -0.5f,  0.87f, 0.0f,  -1.0f,  0.87f, 0.0f,  // left-top
        -0.5f, -0.87f, 0.0f,  -1.0f, -0.87f, 0.0f   // left-bottom
    };



    std::vector<unsigned int> indices = {
    0, 1, 2,  // Face 1
    0, 2, 3,  // Face 2
    0, 3, 1,  // Face 3
    1, 3, 2   // Base
    };

    int segments = 5;

    //int segments = 9;

    //Polygon::GenerateCircle(0.0f, 0.0f, 0.5f, segments, positions, indices);

    VertexArray va;
    VertexBuffer vb(positions.data(), positions.size() * sizeof(float));
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices.data(), indices.size());

    Shader shader("./res/shaders/vertex.shader", "./res/shaders/fragment.shader");

    float r = 1.0f;
    float d = 0.01f;

    while (!glfwWindowShouldClose(window)) {

        // Clear both color and depth buffers every frame!
        GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        shader.Bind();
        va.Bind();
        ib.Bind();

        shader.SetUniform4f("u_color", 1.0f, 1.0f, 1.0f, 1.0f);
        shader.SetUniform3f("u_lightPos", 1.0f, 1.0f, 2.0f);


        glm::mat4 model = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.3f, -3.0f));
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 10.0f);

        /*glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.5f, -2.0f));
        glm::mat4 proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);*/

        shader.SetUniformMat4f("model", model);
        shader.SetUniformMat4f("view", view);
        shader.SetUniformMat4f("proj", proj);



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