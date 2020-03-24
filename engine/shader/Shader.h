//
// Created by david on 24. 03. 2020..
//

#ifndef SURVIVE_SHADER_H
#define SURVIVE_SHADER_H

#include <GL/glew.h>

class Shader
{
private:
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint program;

    static GLuint loadShader(const char *filename, GLenum type);

    static void debug(GLuint shaderId);

public:
    Shader(const char* vertexShaderFile, const char* fragmentShaderFile);

    ~Shader();

    void start();

    static void stop();
};


#endif //SURVIVE_SHADER_H
