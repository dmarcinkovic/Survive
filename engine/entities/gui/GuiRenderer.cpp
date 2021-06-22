//
// Created by david on 28. 03. 2020..
//

#include "Components.h"
#include "GuiRenderer.h"
#include "Maths.h"
#include "Renderer2DUtil.h"

void Survive::GuiRenderer::render(entt::registry &registry) const
{
	auto entities = prepareEntities(registry);

	if (entities.empty())
	{
		return;
	}

	Renderer2DUtil::prepareRendering(m_Shader);
	m_Shader.loadProjectionMatrix(Maths::orthographicProjectionMatrix);

	for (auto const&[texture, guis] : entities)
	{
		Renderer2DUtil::prepareEntity(texture);
		renderGuis(guis, registry, texture);

		Renderer2DUtil::finishRenderingEntity();
	}

	Renderer2DUtil::finishRendering();
}

std::unordered_map<Survive::TexturedModel, std::vector<entt::entity>, Survive::TextureHash>
Survive::GuiRenderer::prepareEntities(entt::registry &registry)
{
	auto view = registry.view<RenderComponent, Transform3DComponent>(entt::exclude<SpriteSheetComponent>);

	std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash> entities;
	for (auto const &entity : view)
	{
		const RenderComponent &renderComponent = view.get<RenderComponent>(entity);

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

		glDrawElements(GL_TRIANGLES, texturedModel.vertexCount(), GL_UNSIGNED_INT, nullptr);
	}
}
