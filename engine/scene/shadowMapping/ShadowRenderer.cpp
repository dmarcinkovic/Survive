//
// Created by david on 22. 05. 2020..
//

#include <glm/glm.hpp>

#include "ShadowRenderer.h"
#include "../../components/RenderComponent.h"
#include "../../components/Transform3DComponent.h"
#include "../../core/math/Maths.h"
#include "../../core/renderer/Renderer3DUtil.h"

void Survive::ShadowRenderer::render(const entt::registry &registry, const Light &light, const Camera &camera) const
{
	Renderer3DUtil::prepareRendering(m_ShadowShader);

	glm::mat4 viewMatrix = Maths::createLightViewMatrix(light);
	m_ShadowShader.loadViewMatrix(viewMatrix);
	m_ShadowShader.loadProjectionMatrix(Maths::lightProjectionMatrix);

	for (auto const&[texture, objects] : m_Objects)
	{
		texture.bind();
		glEnableVertexAttribArray(0);
		for (auto const &object : objects)
		{
			glEnable(GL_CULL_FACE);
			glCullFace(GL_FRONT);

			const Transform3DComponent &transform = registry.get<Transform3DComponent>(object);

			glm::vec3 rotation = transform.rotation + camera.m_Rotation;
			glm::mat4 modelMatrix = Maths::createTransformationMatrix(transform.position, transform.scale, rotation);
			m_ShadowShader.loadTransformationMatrix(modelMatrix);

			glDrawArrays(GL_TRIANGLES, 0, texture.vertexCount());
			glDisable(GL_CULL_FACE);
		}

		Texture::unbindTexture();
		glDisableVertexAttribArray(0);
	}

	Renderer3DUtil::finishRendering();
}

void Survive::ShadowRenderer::add3DObject(const entt::registry &registry, entt::entity entity)
{
	RenderComponent renderComponent = registry.get<RenderComponent>(entity);
	auto &batch = m_Objects[renderComponent.texturedModel];

	batch.emplace_back(entity);
}
