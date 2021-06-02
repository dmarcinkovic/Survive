//
// Created by david on 22. 05. 2020..
//

#include <glm/glm.hpp>

#include "ShadowComponent.h"
#include "ShadowRenderer.h"
#include "RenderComponent.h"
#include "Transform3DComponent.h"
#include "Maths.h"
#include "Renderer3DUtil.h"

void Survive::ShadowRenderer::render(entt::registry &registry, const Light &light, const Camera &camera) const
{
	auto entities = prepareEntities(registry);

	if (entities.empty())
	{
		return;
	}

	Renderer3DUtil::prepareRendering(m_ShadowShader);

	glm::mat4 viewMatrix = Maths::createLightViewMatrix(light);
	m_ShadowShader.loadViewMatrix(viewMatrix);
	m_ShadowShader.loadProjectionMatrix(Maths::lightProjectionMatrix);

	for (auto const&[texture, objects] : entities)
	{
		texture.bind();
		glEnableVertexAttribArray(0);
		for (auto const &object : objects)
		{
			glEnable(GL_CULL_FACE);
			glCullFace(GL_FRONT);

			const Transform3DComponent &transform = registry.get<Transform3DComponent>(object);

			glm::vec3 rotation = transform.rotation + camera.rotation;
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

std::unordered_map<Survive::TexturedModel, std::vector<entt::entity>, Survive::TextureHash>
Survive::ShadowRenderer::prepareEntities(entt::registry &registry)
{
	auto const &view = registry.view<ShadowComponent, Transform3DComponent, RenderComponent>();

	std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash> entities;
	for (auto const &entity : view)
	{
		RenderComponent renderComponent = view.get<RenderComponent>(entity);
		ShadowComponent shadowComponent = view.get<ShadowComponent>(entity);

		if (shadowComponent.loadShadow)
		{
			std::vector<entt::entity> &batch = entities[renderComponent.texturedModel];
			batch.emplace_back(entity);
		}
	}

	return entities;
}
