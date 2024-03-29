//
// Created by david on 28. 03. 2020..
//

#include "Components.h"
#include "GuiRenderer.h"
#include "Maths.h"

void Survive::GuiRenderer::render(entt::registry &registry, const Camera &camera) const
{
	constexpr int numberOfVao = 1;
	auto entities = prepareEntities(registry);

	if (entities.empty())
	{
		return;
	}

	prepareRendering(m_Shader);
	m_Shader.loadProjectionMatrix(camera.getOrthographicProjectionMatrix());

	for (auto const&[texture, guis] : entities)
	{
		prepareEntity(texture, numberOfVao);
		renderGuis(guis, registry, texture);

		finishRenderingEntity(numberOfVao);
	}

	finishRendering();
}

std::unordered_map<Survive::TexturedModel, std::vector<entt::entity>, Survive::TextureHash>
Survive::GuiRenderer::prepareEntities(entt::registry &registry)
{
	auto view = registry.view<Render2DComponent, Transform3DComponent, TagComponent>(entt::exclude<SpriteSheetComponent>);

	std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash> entities;
	for (auto const &entity : view)
	{
		const Render2DComponent &renderComponent = view.get<Render2DComponent>(entity);

		std::vector<entt::entity> &batch = entities[renderComponent.texturedModel];
		batch.emplace_back(entity);
	}

	return entities;
}

void Survive::GuiRenderer::renderGuis(const std::vector<entt::entity> &guis, const entt::registry &registry,
									  const TexturedModel &texturedModel) const
{
	for (auto const &entity : guis)
	{
		const Transform3DComponent &transformComponent = registry.get<Transform3DComponent>(entity);
		m_Shader.loadTransformationMatrix(
				Maths::createTransformationMatrix(transformComponent.position, transformComponent.scale,
												  transformComponent.rotation));

		if (registry.any_of<SpriteComponent>(entity))
		{
			const SpriteComponent &sprite = registry.get<SpriteComponent>(entity);
			m_Shader.loadColor(sprite.color);
		} else
		{
			m_Shader.loadColor(glm::vec4{0.0f});
		}

		glDrawElements(GL_TRIANGLES, texturedModel.vertexCount(), GL_UNSIGNED_INT, nullptr);
	}
}
