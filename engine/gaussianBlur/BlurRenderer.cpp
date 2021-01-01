//
// Created by david on 19. 12. 2020..
//

#include "BlurRenderer.h"
#include "../display/Display.h"

BlurRenderer::BlurRenderer(const Light &light, int width, int height)
		: m_Model(m_Loader.renderQuad()), m_Width(width), m_Height(height), m_HorizontalBlurRenderer(width, height),
		  m_VerticalBlurRenderer(width, height), m_Texture(m_Fbo.createTexture()),
		  m_AnimationRenderer(light)
{

}

void BlurRenderer::render(const Camera &camera) const
{
	glViewport(0,0, m_Width, m_Height);

	m_Fbo.bindDrawBuffer();
	Display::clearWindow();

	m_AnimationRenderer.render(camera);

	FrameBuffer::unbindDrawFrameBuffer();

	auto[screenWidth, screenHeight] = Display::getWindowSize();
	glViewport(0,0, screenWidth, screenHeight);

	prepareRendering();

	m_HorizontalBlurRenderer.render(m_Texture, m_Model);
	m_VerticalBlurRenderer.render(m_HorizontalBlurRenderer.getTexture(), m_Model);

	finishRendering();
}

const Texture &BlurRenderer::getTexture() const
{
	return m_VerticalBlurRenderer.getTexture();
}

void BlurRenderer::prepareRendering() const
{
	glBindVertexArray(m_Model.m_Vao);
	glEnableVertexAttribArray(0);
	glDisable(GL_DEPTH_TEST);
}

void BlurRenderer::finishRendering()
{
	glEnable(GL_DEPTH_TEST);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

void BlurRenderer::addObject(AnimatedObject &object)
{
	m_AnimationRenderer.addAnimatedModel(object);
}
