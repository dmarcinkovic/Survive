//
// Created by david on 22. 05. 2020..
//

#ifndef SURVIVE_FRAMEBUFFER_H
#define SURVIVE_FRAMEBUFFER_H


#include <GL/glew.h>
#include <vector>

class FrameBuffer
{
private:
    GLuint m_FrameBuffer{};
    std::vector<GLuint> m_Textures;
    std::vector<GLuint> m_RenderBuffers;

public:
    FrameBuffer();

    ~FrameBuffer();

    void bindFrameBuffer() const;

    static void unbindFrameBuffer();

    GLuint createTexture();

    GLuint attachToDepthBufferTexture();

private:
    void attachDepthComponent(int width, int height);

    GLuint createTexture(int width, int height, GLint internalFormat, GLenum format, GLenum type);
};


#endif //SURVIVE_FRAMEBUFFER_H
