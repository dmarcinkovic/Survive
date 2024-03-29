//
// Created by david on 19. 12. 2020..
//

#include "BlurRenderer.h"
#include "Display.h"

Survive::BlurRenderer::BlurRenderer(const Light &light, int width, int height)
		: m_AnimationRenderer(light), m_ObjectRenderer(light),
		  m_Model(m_Loader.renderQuad()), m_Light(light), m_Texture(m_Fbo.createTexture()),
		  m_HorizontalBlurRenderer(width, height), m_VerticalBlurRenderer(width, height)
{
	auto[screenWidth, screenHeight] = Display::getWindowSize<int>();

	m_Width = screenWidth;
	m_Height = screenHeight;
}

void Survive::BlurRenderer::render(entt::registry &registry, const Camera &camera) const
{
	renderToFbo(registry, camera);
	renderBlur();
}

const Survive::Texture &Survive::BlurRenderer::getTexture() const
{
	return m_VerticalBlurRenderer.getTexture();
}

void Survive::BlurRenderer::prepareRendering() const
{
	glBindVertexArray(m_Model.m_Vao);
	glEnableVertexAttribArray(0);
	glDisable(GL_DEPTH_TEST);
}

void Survive::BlurRenderer::finishRendering()
{
	glEnable(GL_DEPTH_TEST);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

void Survive::BlurRenderer::renderToFbo(entt::registry &registry, const Camera &camera) const
{
	glViewport(0, 0, m_Width, m_Height);

	m_Fbo.bindDrawBuffer();
	Display::clearWindow();

	m_AnimationRenderer.renderAnimation(registry, camera, 0);
	m_ObjectRenderer.render(registry, camera, 0);
	m_TerrainRenderer.render(registry, camera, m_Light, 0);

	FrameBuffer::unbindDrawFrameBuffer();

	auto[screenWidth, screenHeight] = Display::getWindowSize<int>();
	glViewport(0, 0, screenWidth, screenHeight);
}

void Survive::BlurRenderer::renderBlur() const
{
	prepareRendering();

	m_HorizontalBlurRenderer.render(m_Texture, m_Model);
	m_VerticalBlurRenderer.render(m_HorizontalBlurRenderer.getTexture(), m_Model);

	finishRendering();
}
