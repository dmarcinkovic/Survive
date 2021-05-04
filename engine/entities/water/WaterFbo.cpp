//
// Created by david on 17. 10. 2020..
//

#include "WaterFbo.h"
#include "../../core/display/Display.h"

Survive::WaterFbo::WaterFbo()
{
	initializeReflectionFrameBuffer();
	initializeRefractionFrameBuffer();
}

void Survive::WaterFbo::initializeRefractionFrameBuffer()
{
	m_FboRefraction.bindFrameBuffer();
	FrameBuffer::drawBuffer();
	m_RefractionColorTexture = Texture(m_FboRefraction.attachColorComponent(REFRACTION_WIDTH, REFRACTION_HEIGHT));
	m_RefractionDepthTexture = Texture(
			m_FboRefraction.createDepthTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT));

	unbindFrameBuffer();
}

void Survive::WaterFbo::initializeReflectionFrameBuffer()
{
	m_FboReflection.bindFrameBuffer();
	FrameBuffer::drawBuffer();
	m_ReflectionColorTexture = Texture(m_FboReflection.attachColorComponent(REFLECTION_WIDTH, REFLECTION_HEIGHT));
	m_FboReflection.attachDepthComponent(REFLECTION_WIDTH, REFLECTION_HEIGHT);

	unbindFrameBuffer();
}

const Survive::Texture &Survive::WaterFbo::reflectionColorTexture() const
{
	return m_ReflectionColorTexture;
}

const Survive::Texture &Survive::WaterFbo::refractionColorTexture() const
{
	return m_RefractionColorTexture;
}

const Survive::Texture &Survive::WaterFbo::getRefractionDepthBuffer() const
{
	return m_RefractionDepthTexture;
}

void Survive::WaterFbo::bindReflectionFrameBuffer() const
{
	m_FboReflection.bindFrameBuffer();
	glViewport(0, 0, REFLECTION_WIDTH, REFLECTION_HEIGHT);
}

void Survive::WaterFbo::bindRefractionFrameBuffer() const
{
	m_FboRefraction.bindFrameBuffer();
	glViewport(0, 0, REFRACTION_WIDTH, REFRACTION_HEIGHT);
}

void Survive::WaterFbo::unbindFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	auto[width, height] = Display::getWindowSize<int>();
	glViewport(0, 0, width, height);
}
