//
// Created by david on 10. 01. 2021..
//

#include "BloomRenderer.h"

BloomRenderer::BloomRenderer(int width, int height)
		: m_HorizontalRenderer(width, height), m_VerticalRenderer(width, height), m_Model(m_Loader.renderQuad())
{

}

void BloomRenderer::render() const
{
	if (m_Objects.empty())
	{
		return;
	}

	prepare();

	for (auto const& object : m_Objects)
	{
		const Texture &emissiveTexture = object.get().getEmissiveTexture();

		m_HorizontalRenderer.render(emissiveTexture, m_Model);
		m_VerticalRenderer.render(m_HorizontalRenderer.getTexture(), m_Model);
	}

	finishRendering();
}

void BloomRenderer::prepare() const
{
	glBindVertexArray(m_Model.m_Vao);
	glEnableVertexAttribArray(0);
	glDisable(GL_DEPTH_TEST);
}

void BloomRenderer::finishRendering()
{
	glEnable(GL_DEPTH_TEST);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

void BloomRenderer::addObject(Object3D &object)
{
	m_Objects.emplace_back(object);
	object.addBloomTexture(m_VerticalRenderer.getTexture());
}
