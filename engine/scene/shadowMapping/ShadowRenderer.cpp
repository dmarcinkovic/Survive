//
// Created by david on 22. 05. 2020..
//

#include <glm/glm.hpp>

#include "Components.h"
#include "ShadowRenderer.h"
#include "Maths.h"

void Survive::ShadowRenderer::render(entt::registry &registry, const Light &light, const Camera &camera) const
{
	auto entities = prepareEntities(registry);

	if (entities.empty())
	{
		return;
	}

	prepareRendering(m_ShadowShader);

	m_ShadowShader.loadViewMatrix(light.getViewMatrix());
	m_ShadowShader.loadProjectionMatrix(camera.getLightProjectionMatrix());

	for (auto const &[texture, objects]: entities)
	{
		texture.bind();
		glEnableVertexAttribArray(0);
		for (auto const &object: objects)
		{
			glEnable(GL_CULL_FACE);
			glCullFace(GL_FRONT);

			const Transform3DComponent &transform = registry.get<Transform3DComponent>(object);
			glm::mat4 modelMatrix = Maths::createTransformationMatrix(transform.position, transform.scale,
																	  transform.rotation);

			m_ShadowShader.loadTransformationMatrix(modelMatrix);

			if (registry.any_of<AnimationComponent>(object))
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

	finishRendering();
}

std::unordered_map<Survive::TexturedModel, std::vector<entt::entity>, Survive::TextureHash>
Survive::ShadowRenderer::prepareEntities(entt::registry &registry)
{
	auto const &view = registry.view<ShadowComponent, Transform3DComponent, TagComponent>();

	std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash> entities;
	for (auto const &entity: view)
	{
		TexturedModel model;
		if (registry.any_of<Render3DComponent>(entity))
		{
			model = registry.get<Render3DComponent>(entity).texturedModel;
		} else if (registry.any_of<TerrainComponent>(entity))
		{
			model = registry.get<TerrainComponent>(entity).terrainModel;
		} else
		{
			continue;
		}

		const ShadowComponent &shadowComponent = view.get<ShadowComponent>(entity);

		if (shadowComponent.loadShadow)
		{
			std::vector<entt::entity> &batch = entities[model];
			batch.emplace_back(entity);
		}
	}

	return entities;
}
