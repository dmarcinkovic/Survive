//
// Created by david on 17. 10. 2020..
//

#include "WaterFbo.h"
#include "../display/Display.h"

WaterFbo::WaterFbo()
{
	initializeReflectionFrameBuffer();
	initializeRefractionFrameBuffer();
}

void WaterFbo::initializeRefractionFrameBuffer()
{
	m_FboRefraction.bindFrameBuffer();
	FrameBuffer::drawBuffer();
	m_refractionTexture = m_FboRefraction.createColorTexture(REFRACTION_WIDTH, REFRACTION_HEIGHT);
	m_FboRefraction.attachDepthComponent(REFRACTION_WIDTH, REFRACTION_HEIGHT);
}

void WaterFbo::initializeReflectionFrameBuffer()
{
	m_FboReflection.bindFrameBuffer();
	FrameBuffer::drawBuffer();
	m_reflectionTexture = m_FboReflection.createColorTexture(REFLECTION_WIDTH, REFLECTION_HEIGHT);
	m_FboReflection.attachDepthComponent(REFLECTION_WIDTH, REFLECTION_HEIGHT);
}

GLuint WaterFbo::reflectionTexture() const
{
	return m_reflectionTexture;
}

GLuint WaterFbo::refractionTexture() const
{
	return m_refractionTexture;
}

GLuint WaterFbo::getRefractionDepthBuffer() const
{
	return m_FboRefraction.getRenderBuffer(0);
}

void WaterFbo::bindReflectionFrameBuffer() const
{
	m_FboReflection.bindFrameBuffer();
	glViewport(0, 0, REFLECTION_WIDTH, REFLECTION_HEIGHT);
}

void WaterFbo::bindRefractionFrameBuffer() const
{
	m_FboRefraction.bindFrameBuffer();
	glViewport(0, 0, REFRACTION_WIDTH, REFRACTION_HEIGHT);
}

void WaterFbo::unbindFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	auto[width, height] = Display::getWindowSize<int>();
	glViewport(0, 0, width, height);
}
