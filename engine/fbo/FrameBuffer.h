//
// Created by david on 22. 05. 2020..
//

#ifndef SURVIVE_FRAMEBUFFER_H
#define SURVIVE_FRAMEBUFFER_H


#include <GL/glew.h>
#include <vector>
#include "../renderer/Renderer3D.h"

class FrameBuffer
{
private:
    GLuint m_FrameBuffer{};
    std::vector<GLuint> m_Textures;
    std::vector<GLuint> m_RenderBuffers;

public:
    FrameBuffer();

    ~FrameBuffer();

    void renderToFrameBuffer(const Renderer3D &renderer, const Camera &camera) const;

    GLuint createTexture();

    GLuint attachToDepthBufferTexture();

private:
    void attachDepthComponent(int width, int height);

    static void unbindFrameBuffer();

    void bindFrameBuffer() const;

    GLuint createTexture(int width, int height, GLint internalFormat, GLenum format, GLenum type);
};


#endif //SURVIVE_FRAMEBUFFER_H
