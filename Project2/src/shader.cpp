#include "Shader.h"
#include "renderer.h"

#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
    : m_RendererID(0)
{
    std::string vertexShader = ReadFile(vertexPath);
    std::string fragmentShader = ReadFile(fragmentPath);
    m_RendererID = CreateShader(vertexShader, fragmentShader);
}

Shader::~Shader() {
    GLCALL(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const {
    GLCALL(glUseProgram(m_RendererID));
}

void Shader::Unbind() const {
    GLCALL(glUseProgram(0));
}

std::string Shader::ReadFile(const std::string& path) {
    std::ifstream stream(path);
    std::stringstream buffer;
    buffer << stream.rdbuf();
    return buffer.str();
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    GLCALL(glShaderSource(id, 1, &src, nullptr));
    GLCALL(glCompileShader(id));

    int result;
    GLCALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
        int length;
        GLCALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)_malloca(length * sizeof(char));
        GLCALL(glGetShaderInfoLog(id, length, &length, message));
        std::cerr << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment")
            << " shader compile error: " << message << std::endl;
        GLCALL(glDeleteShader(id));
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCALL(glAttachShader(program, vs));
    GLCALL(glAttachShader(program, fs));
    GLCALL(glLinkProgram(program));
    GLCALL(glValidateProgram(program));

    GLCALL(glDeleteShader(vs));
    GLCALL(glDeleteShader(fs));

    return program;
}

int Shader::GetUniformLocation(const std::string& name) {
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    int location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location == -1)
        std::cerr << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;

    m_UniformLocationCache[name] = location;
    return location;
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
    GLCALL(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}
