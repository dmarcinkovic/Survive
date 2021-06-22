//
// Created by david on 25. 12. 2020..
//

#include "SkyRenderer.h"
#include "Maths.h"

void Survive::SkyRenderer::render(const entt::registry &registry, const Camera &camera, const glm::vec4 &plane) const
{
	if (m_ShouldRender)
	{
		const Render3DComponent &renderComponent = registry.get<Render3DComponent>(m_Sky);
		const Transform3DComponent &transform = registry.get<Transform3DComponent>(m_Sky);

		prepareRendering(renderComponent);
		loadUniforms(registry, transform, camera, plane);

		glDrawElements(GL_TRIANGLES, renderComponent.texturedModel.vertexCount(), GL_UNSIGNED_INT, nullptr);

		finishRendering();
	}
}

void Survive::SkyRenderer::addSkyEntity(entt::entity sky)
{
	m_Sky = sky;
	m_ShouldRender = true;
}

void Survive::SkyRenderer::prepareRendering(const Render3DComponent &renderComponent) const
{
	m_Shader.start();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glBindVertexArray(renderComponent.texturedModel.vaoID());
	glEnableVertexAttribArray(0);

	renderComponent.texturedModel.bindCubeTexture(0);
}

void Survive::SkyRenderer::finishRendering()
{
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);

	Texture::unbindCubeTexture();

	glDepthFunc(GL_LESS);
	glDisable(GL_DEPTH_TEST);
	SkyShader::stop();
}

void Survive::SkyRenderer::loadUniforms(const entt::registry &registry, const Transform3DComponent &transform,
										const Camera &camera, const glm::vec4 &plane) const
{
	auto viewMatrix = Maths::createViewMatrix(camera);
	viewMatrix[3][0] = 0;
	viewMatrix[3][1] = 0;
	viewMatrix[3][2] = 0;

	float skyRotation = 0.0f;

	if (registry.has<MoveComponent>(m_Sky))
	{
		const MoveComponent &moveComponent = registry.get<MoveComponent>(m_Sky);
		skyRotation = moveComponent.currentMoveValue;
	}

	viewMatrix = glm::rotate(viewMatrix, glm::radians(skyRotation), glm::vec3{0, 1, 0});

	auto projectionMatrix = Maths::projectionMatrix;
	m_Shader.loadViewAndProjectionMatrices(viewMatrix, projectionMatrix);

	auto transformationMatrix = Maths::createTransformationMatrix(transform.position, transform.scale);
	m_Shader.loadTransformationMatrix(transformationMatrix);
	m_Shader.loadPlane(plane);
}
