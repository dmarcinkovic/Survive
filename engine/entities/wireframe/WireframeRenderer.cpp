//
// Created by david on 24. 01. 2022..
//

#include "WireframeRenderer.h"
#include "Renderer2DUtil.h"

Survive::WireframeRenderer::WireframeRenderer()
{
	std::vector<float> vertices{-0.5f, -0.5f,
								0.5f, -0.5f,
								-0.5f, 0.5f};
	auto[model, vbo] = m_Loader.loadToVao(vertices, 2);

	m_Model = model;
	m_Vbo = vbo;
}

void Survive::WireframeRenderer::render() const
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	Renderer2DUtil::prepareRendering(m_Shader);
	glBindVertexArray(m_Model.m_Vao);
	glEnableVertexAttribArray(0);

	glDrawArrays(GL_TRIANGLES, 0, m_Model.m_VertexCount);

	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	Renderer2DUtil::finishRendering();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
