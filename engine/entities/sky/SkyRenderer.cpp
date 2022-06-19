//
// Created by david on 25. 12. 2020..
//

#include "SkyRenderer.h"
#include "Transform3DComponent.h"
#include "SkyboxComponent.h"
#include "Maths.h"

void Survive::SkyRenderer::render(entt::registry &registry, const Camera &camera, const glm::vec4 &plane) const
{
	auto entities = registry.view<SkyboxComponent, Transform3DComponent>();

	if (entities.begin() == entities.end())
	{
		return;
	}

	prepareRendering(m_Shader);
	glDepthFunc(GL_LEQUAL);
	for (auto const &entity: entities)
	{
		const SkyboxComponent &skybox = entities.get<SkyboxComponent>(entity);
		const Transform3DComponent &transform = entities.get<Transform3DComponent>(entity);

		prepareRenderingSky(skybox);

		loadUniforms(registry, transform, camera, plane);
		glDrawElements(GL_TRIANGLES, skybox.skyboxModel.vertexCount(), GL_UNSIGNED_INT, nullptr);

		finishRenderingSky();
	}
	glDepthFunc(GL_LESS);
	finishRendering();
}

void Survive::SkyRenderer::prepareRenderingSky(const SkyboxComponent &skyComponent)
{
	glBindVertexArray(skyComponent.skyboxModel.vaoID());
	glEnableVertexAttribArray(0);

	skyComponent.skyboxModel.bindCubeTexture(0);
}

void Survive::SkyRenderer::finishRenderingSky()
{
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);

	Texture::unbindCubeTexture();
}

void Survive::SkyRenderer::loadUniforms(const entt::registry &registry, const Transform3DComponent &transform,
										const Camera &camera, const glm::vec4 &plane) const
{
	glm::mat4 viewMatrix = camera.getViewMatrix();
	viewMatrix[3][0] = 0;
	viewMatrix[3][1] = 0;
	viewMatrix[3][2] = 0;

	m_Shader.loadViewAndProjectionMatrices(viewMatrix, camera.getProjectionMatrix());

	auto transformationMatrix = Maths::createTransformationMatrix(transform.position, transform.scale);
	m_Shader.loadTransformationMatrix(transformationMatrix);
	m_Shader.loadPlane(plane);
}
