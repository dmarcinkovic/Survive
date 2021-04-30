//
// Created by david on 10. 01. 2021..
//

#include "BloomRenderer.h"

BloomRenderer::BloomRenderer(int width, int height)
		: m_HorizontalRenderer(width, height), m_VerticalRenderer(width, height), m_Model(m_Loader.renderQuad())
{

}

void BloomRenderer::render(entt::registry &registry) const
{
	auto const &view = registry.view<BloomComponent>();

	if (view.empty())
	{
		return;
	}

	prepare();

	for (auto const &entity : view)
	{
		BloomComponent &bloom = view.get<BloomComponent>(entity);

		m_HorizontalRenderer.render(bloom.emissiveTexture, m_Model);
		m_VerticalRenderer.render(m_HorizontalRenderer.getTexture(), m_Model);

		bloom.bloomTexture = m_VerticalRenderer.getTexture();
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
