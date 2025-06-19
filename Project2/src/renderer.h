#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "indexBuffer.h"
#include "vertexBuffer.h"
#include "shader.h"

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCALL(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);
