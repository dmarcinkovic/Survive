//
// Created by david on 24. 03. 2020..
//

#ifndef SURVIVE_SHADER_H
#define SURVIVE_SHADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>

class Shader
{
protected:
    GLuint m_VertexShader;
    GLuint m_FragmentShader;
    GLuint m_Program;

private:
    static GLuint loadShader(const char *filename, GLenum type);

    static void debug(GLuint shaderId);

public:
    Shader(const char *vertexShaderFile, const char *fragmentShaderFile);

    ~Shader();

    void start() const;

    static void stop();

protected:
    static void loadMatrix(GLuint location, const glm::mat4 &matrix);

    static void loadVector3(GLuint location, const glm::vec3 &vector);

    static void loadFloat(GLuint location, float value);

    static void loadVector4(GLuint location, const glm::vec4 &vector);
};


#endif //SURVIVE_SHADER_H
