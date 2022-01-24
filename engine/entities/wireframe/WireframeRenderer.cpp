//
// Created by david on 24. 01. 2022..
//

#include "WireframeRenderer.h"
#include "Renderer3DUtil.h"
#include <iostream>

std::vector<float> Survive::WireframeRenderer::m_Vertices{};
GLuint Survive::WireframeRenderer::m_Vbo{};

Survive::WireframeRenderer::WireframeRenderer()
{
	auto[model, vbo] = m_Loader.loadToVao(MAX_VERTICES, 3);

	m_Model = model;
	m_Vbo = vbo;
}

void Survive::WireframeRenderer::render() const
{
	if (m_Vertices.empty())
	{
		return;
	}

	prepareRendering();

	glDrawArrays(GL_TRIANGLES, 0, m_Model.m_VertexCount);

	finish();
}

void Survive::WireframeRenderer::prepareRendering() const
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	Renderer3DUtil::prepareRendering(m_Shader);
	glBindVertexArray(m_Model.m_Vao);
	glEnableVertexAttribArray(0);
}

void Survive::WireframeRenderer::finish()
{
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	Renderer3DUtil::finishRendering();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Survive::WireframeRenderer::updateData(std::vector<float> vertices)
{
	m_Vertices = std::move(vertices);

	auto sizeOfData = static_cast<GLsizeiptr>(m_Vertices.size());
	Loader::updateVBO(m_Vbo, m_Vertices, sizeOfData);
}
