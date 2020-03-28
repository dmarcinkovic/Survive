//
// Created by david on 24. 03. 2020..
//

#ifndef SURVIVE_SHADER_H
#define SURVIVE_SHADER_H

#include <GL/glew.h>

class Shader
{
private:
    GLuint m_VertexShader;
    GLuint m_FragmentShader;
    GLuint m_Program;

    static GLuint loadShader(const char *filename, GLenum type);

    static void debug(GLuint shaderId);

public:
    Shader(const char* vertexShaderFile, const char* fragmentShaderFile);

    ~Shader();

    void start() const;

    static void stop();
};


#endif //SURVIVE_SHADER_H
