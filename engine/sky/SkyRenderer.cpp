//
// Created by david on 25. 12. 2020..
//

#include "SkyRenderer.h"
#include "../math/Maths.h"
#include "../display/Display.h"

void SkyRenderer::render(const Camera &camera, const glm::vec4 &plane) const
{
	if (m_ShouldRender)
	{
		prepareRendering();
		loadUniforms(camera, plane);

		glDrawElements(GL_TRIANGLES, m_Sky.m_Texture.vertexCount(), GL_UNSIGNED_INT, nullptr);

		finishRendering();
	}
}

void SkyRenderer::addSkyEntity(const Entity &sky)
{
	m_Sky = sky;
	m_ShouldRender = true;
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

	Texture::unbindCubeTexture();

	glDepthFunc(GL_LESS);
	glDisable(GL_DEPTH_TEST);
	SkyShader::stop();
}

void SkyRenderer::loadUniforms(const Camera &camera, const glm::vec4 &plane) const
{
	auto viewMatrix = Maths::createViewMatrix(camera);
	viewMatrix[3][0] = 0;
	viewMatrix[3][1] = 0;
	viewMatrix[3][2] = 0;

	viewMatrix = glm::rotate(viewMatrix, glm::radians(m_Rotation), glm::vec3{0, 1, 0});

	auto projectionMatrix = Maths::projectionMatrix;
	m_Shader.loadViewAndProjectionMatrices(viewMatrix, projectionMatrix);

	auto transformationMatrix = Maths::createTransformationMatrix(m_Sky.m_Position, m_Sky.m_Scale);
	m_Shader.loadTransformationMatrix(transformationMatrix);
	m_Shader.loadPlane(plane);
}

void SkyRenderer::rotateSky()
{
	auto deltaTime = static_cast<float>(Display::getFrameTime());
	m_Rotation += ROTATE_SPEED * deltaTime;
}
