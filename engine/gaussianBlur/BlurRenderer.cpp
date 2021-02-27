//
// Created by david on 19. 12. 2020..
//

#include "BlurRenderer.h"
#include "../display/Display.h"

BlurRenderer::BlurRenderer(const Light &light, int width, int height)
		: m_AnimationRenderer(light), m_ObjectRenderer(light),
		  m_Model(m_Loader.renderQuad()), m_Light(light), m_Texture(m_Fbo.createTexture()),
		  m_HorizontalBlurRenderer(width, height), m_VerticalBlurRenderer(width, height)
{
	auto[screenWidth, screenHeight] = Display::getWindowSize<int>();

	m_Width = screenWidth;
	m_Height = screenHeight;
}

void BlurRenderer::render(const Camera &camera) const
{
	if (!m_ShouldRender)
	{
		return;
	}

	renderToFbo(camera);
	renderBlur();
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

void BlurRenderer::addAnimatedObject(AnimatedObject &animatedObject)
{
	m_AnimationRenderer.addAnimatedModel(animatedObject);
	m_ShouldRender = true;
}

void BlurRenderer::addObject(Object3D &object)
{
	m_ObjectRenderer.add3DObject(object);
	m_ShouldRender = true;
}

void BlurRenderer::addTerrain(Terrain &terrain)
{
	m_TerrainRenderer.addTerrain(terrain);
	m_ShouldRender = true;
}

void BlurRenderer::renderToFbo(const Camera &camera) const
{
	glViewport(0, 0, m_Width, m_Height);

	m_Fbo.bindDrawBuffer();
	Display::clearWindow();

	m_AnimationRenderer.render(camera);
	m_ObjectRenderer.render(camera, 0);
	m_TerrainRenderer.render(camera,m_Light, 0);

	FrameBuffer::unbindDrawFrameBuffer();

	auto[screenWidth, screenHeight] = Display::getWindowSize<int>();
	glViewport(0, 0, screenWidth, screenHeight);
}

void BlurRenderer::renderBlur() const
{
	prepareRendering();

	m_HorizontalBlurRenderer.render(m_Texture, m_Model);
	m_VerticalBlurRenderer.render(m_HorizontalBlurRenderer.getTexture(), m_Model);

	finishRendering();
}
