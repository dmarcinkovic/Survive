//
// Created by david on 25. 12. 2020..
//

#include "SkyRenderer.h"
#include "../math/Maths.h"

SkyRenderer::SkyRenderer(Entity &sky)
	: m_Sky(sky)
{

}

void SkyRenderer::render(const Camera &camera) const
{
	glDepthMask(GL_FALSE);
	m_Shader.start();

	glBindVertexArray(m_Sky.m_Texture.vaoID());
	glEnableVertexAttribArray(0);

	m_Sky.m_Texture.bindCubeTexture(0);

	auto viewMatrix = Maths::createViewMatrix(camera);
	auto projectionMatrix = Maths::projectionMatrix;
	m_Shader.loadViewAndProjectionMatrices(viewMatrix, projectionMatrix);

	glDrawElements(GL_TRIANGLES, m_Sky.m_Texture.vertexCount(), GL_UNSIGNED_INT, nullptr);

	glDisableVertexAttribArray(0);
	glBindVertexArray(0);

	SkyShader::stop();
	glDepthMask(GL_TRUE);
}
