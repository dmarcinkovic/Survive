//
// Created by david on 22. 05. 2020..
//

#include <glm/glm.hpp>

#include "Components.h"
#include "ShadowRenderer.h"
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

	m_ShadowShader.loadViewMatrix(light.getViewMatrix());
	m_ShadowShader.loadProjectionMatrix(light.getProjectionMatrix());

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

			if (registry.has<AnimationComponent>(object))
			{
				const AnimationComponent &animation = registry.get<AnimationComponent>(object);

				m_ShadowShader.loadAnimatedModel(true);
				m_ShadowShader.loadJointTransforms(animation.jointTransforms);
			} else
			{
				m_ShadowShader.loadAnimatedModel(false);
			}

			glDrawElements(GL_TRIANGLES, texture.vertexCount(), GL_UNSIGNED_INT, nullptr);
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
	auto const &view = registry.view<ShadowComponent, Transform3DComponent, Render3DComponent>();

	std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash> entities;
	for (auto const &entity : view)
	{
		Render3DComponent renderComponent = view.get<Render3DComponent>(entity);
		ShadowComponent shadowComponent = view.get<ShadowComponent>(entity);

		if (shadowComponent.loadShadow)
		{
			std::vector<entt::entity> &batch = entities[renderComponent.texturedModel];
			batch.emplace_back(entity);
		}
	}

	return entities;
}
