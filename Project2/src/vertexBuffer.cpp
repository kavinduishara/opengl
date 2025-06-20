#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "vertexBuffer.h"
#include "renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    GLCALL(glGenBuffers(1, &m_RendererID));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    GLCALL(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const
{
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const
{
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
