//
// Created by david on 22. 05. 2020..
//

#include "FrameBuffer.h"
#include "../display/Display.h"

FrameBuffer::FrameBuffer()
{
    glGenFramebuffers(1, &m_FrameBuffer);
}

FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &m_FrameBuffer);
    glDeleteTextures(m_Textures.size(), m_Textures.data());
    glDeleteRenderbuffers(m_RenderBuffers.size(), m_RenderBuffers.data());
}

void FrameBuffer::bindFrameBuffer() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);
}

void FrameBuffer::unbindFrameBuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint FrameBuffer::createTexture()
{
    bindFrameBuffer();

    auto[width, height] = Display::getWindowSize();
    GLuint texture = createTexture(width, height, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);
    attachDepthComponent(width, height);

    unbindFrameBuffer();
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

GLuint FrameBuffer::attachToDepthBufferTexture()
{
    bindFrameBuffer();

    auto[width, height] = Display::getWindowSize();
    GLuint texture = createTexture(width, height, GL_DEPTH_COMPONENT32, GL_DEPTH_COMPONENT, GL_FLOAT);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture, 0);
    attachDepthComponent(width, height);

    unbindFrameBuffer();
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

GLuint FrameBuffer::createTexture(int width, int height, GLint internalFormat, GLenum format, GLenum type)
{
    GLuint texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    m_Textures.emplace_back(texture);
    return texture;
}

void FrameBuffer::attachDepthComponent(int width, int height)
{
    GLuint renderBuffer;
    glGenRenderbuffers(1, &renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    m_RenderBuffers.emplace_back(renderBuffer);
}

void FrameBuffer::renderToFrameBuffer(const Renderer3D &renderer, const Camera &camera) const
{
    bindFrameBuffer();
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    renderer.render(camera);

    unbindFrameBuffer();
}
