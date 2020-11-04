//
// Created by david on 22. 05. 2020..
//

#include <iostream>
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
	std::cout << "Binding framebuffer: " << m_FrameBuffer << '\n';
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
    GLuint texture = createColorTexture(width, height);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);
    attachDepthComponent(width, height);

    unbindFrameBuffer();
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

GLuint FrameBuffer::attachToDepthBufferTexture()
{
    bindFrameBuffer();

    GLuint texture = createDepthTexture(SHADOW_WIDTH, SHADOW_HEIGHT);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture, 0);

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    unbindFrameBuffer();
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

GLuint FrameBuffer::createColorTexture(int width, int height)
{
    GLuint texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    m_Textures.emplace_back(texture);
    return texture;
}

GLuint FrameBuffer::createDepthTexture(int width, int height)
{
    GLuint texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    float borderColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

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

void FrameBuffer::renderToFrameBuffer(const ShadowRenderer &renderer, const Camera &camera, const Light &light) const
{
    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);

    bindFrameBuffer();
    glClear(GL_DEPTH_BUFFER_BIT);

    renderer.render(light, camera);

//    unbindFrameBuffer();

    auto[width, height] = Display::getWindowSize();
    glViewport(0, 0, width, height);
}
