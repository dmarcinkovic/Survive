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
	glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);
}

void FrameBuffer::unbindFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint FrameBuffer::createTexture()
{
	auto[width, height] = Display::getWindowSize<int>();

	return createTexture(width, height);
}

GLuint FrameBuffer::createTexture(int width, int height)
{
	bindFrameBuffer();
	GLuint texture = attachColorComponent(width, height);

	attachDepthComponent(width, height);

	unbindFrameBuffer();
	glBindTexture(GL_TEXTURE_2D, 0);

	return texture;
}

GLuint FrameBuffer::attachToDepthBufferTexture(int width, int height)
{
	bindFrameBuffer();

	GLuint texture = createDepthTexture(width, height);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture, 0);

	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	unbindFrameBuffer();
	glBindTexture(GL_TEXTURE_2D, 0);

	return texture;
}

GLuint FrameBuffer::attachColorComponent(int width, int height)
{
	GLuint colorComponent = createColorTexture(width, height);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, colorComponent, 0);

	return colorComponent;
}

GLuint FrameBuffer::createColorTexture(int width, int height)
{
	GLuint texture;
	glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
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
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	m_RenderBuffers.emplace_back(renderBuffer);
}

void
FrameBuffer::renderToFrameBuffer(const ShadowRenderer &renderer, const Camera &camera, const Light &light, int width,
								 int height) const
{
	glViewport(0, 0, width, height);

	bindFrameBuffer();
	glClear(GL_DEPTH_BUFFER_BIT);

	renderer.render(light, camera);

	unbindFrameBuffer();

	auto[w, h] = Display::getWindowSize<int>();
	glViewport(0, 0, w, h);
}

void FrameBuffer::attachColorAttachment(GLuint texture)
{
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
}

void FrameBuffer::bindDrawBuffer() const
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_FrameBuffer);
}

void FrameBuffer::unbindDrawFrameBuffer()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void FrameBuffer::drawBuffer()
{
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
}

GLuint FrameBuffer::getRenderBuffer(int renderBufferNumber) const
{
	return m_RenderBuffers[renderBufferNumber];
}

GLuint FrameBuffer::createDepthTextureAttachment(int width, int height)
{
	GLuint texture;
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture, 0);

	m_Textures.emplace_back(texture);
	return texture;
}
