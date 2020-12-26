//
// Created by david on 25. 12. 2020..
//

#include "SkyRenderer.h"
#include "../math/Maths.h"

void SkyRenderer::render(const Camera &camera) const
{
	prepareRendering();

	auto viewMatrix = Maths::createViewMatrix(camera);
	auto projectionMatrix = Maths::projectionMatrix;
	m_Shader.loadViewAndProjectionMatrices(viewMatrix, projectionMatrix);

	glDrawElements(GL_TRIANGLES, m_Sky.m_Texture.vertexCount(), GL_UNSIGNED_INT, nullptr);

	finishRendering();
}

void SkyRenderer::addSkyEntity(const Entity &sky)
{
	m_Sky = sky;
}

void SkyRenderer::prepareRendering() const
{
	m_Shader.start();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glBindVertexArray(m_Sky.m_Texture.vaoID());
	glEnableVertexAttribArray(0);

	m_Sky.m_Texture.bindCubeTexture(0);
}

void SkyRenderer::finishRendering()
{
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);

	glDepthFunc(GL_LESS);
	glDisable(GL_DEPTH_TEST);
	SkyShader::stop();
}
