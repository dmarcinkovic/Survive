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
	auto const &view = registry.view<ShadowComponent, Transform3DComponent, Render3DComponent, TagComponent>();

	std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash> entities;
	for (auto const &entity: view)
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
