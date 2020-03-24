//
// Created by david on 24. 03. 2020..
//

#include <alloca.h>
#include <iostream>
#include <fstream>

#include "Shader.h"

Shader::Shader(const char* vertexShaderFile, const char* fragmentShaderFile)
{
    vertexShader = loadShader(vertexShaderFile,GL_VERTEX_SHADER);
    fragmentShader = loadShader(fragmentShaderFile, GL_FRAGMENT_SHADER);

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);
    glValidateProgram(program);
}

Shader::~Shader()
{
    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(program);
}

void Shader::start()
{
    glUseProgram(program);
}

void Shader::stop()
{
    glUseProgram(0);
}

GLuint Shader::loadShader(const char *filename, GLenum type)
{
    std::ifstream reader(filename);
    std::string source((std::istreambuf_iterator<char>(reader)),
                       std::istreambuf_iterator<char>());

    GLuint shader = glCreateShader(type);

    const char* shaderSource = source.c_str();
    glShaderSource(shader, 1, &shaderSource,nullptr);
    glCompileShader(shader);

    debug(shader);

    reader.close();
    return shader;
}

void Shader::debug(GLuint shaderId)
{
    int result;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *) alloca(length * sizeof(char));

        glGetShaderInfoLog(shaderId, length, &length, message);

        std::cout << "Error while compiling shader: " << message << "\n";
        glDeleteShader(shaderId);
    }
}
