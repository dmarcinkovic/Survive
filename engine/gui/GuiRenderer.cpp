//
// Created by david on 28. 03. 2020..
//

#include "GuiRenderer.h"
#include "../math/Maths.h"
#include "../renderer/Renderer2DUtil.h"
#include "../display/Display.h"
#include "../components/RenderComponent.h"
#include "../components/Transform2DComponent.h"
#include "../components/SpriteSheetComponent.h"

void GuiRenderer::render(entt::registry &registry) const
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

std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash>
GuiRenderer::prepareEntities(entt::registry &registry)
{
	auto view = registry.view<RenderComponent, Transform2DComponent>(entt::exclude<SpriteSheetComponent>);

	std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash> entities;
	for (auto const &entity : view)
	{
		const RenderComponent &renderComponent = view.get<RenderComponent>(entity);

		std::vector<entt::entity> &batch = entities[renderComponent.texturedModel];
		batch.emplace_back(entity);
	}

	return entities;
}

void GuiRenderer::renderGuis(const std::vector<entt::entity> &guis, const entt::registry &registry,
							 const TexturedModel &texturedModel) const
{
	for (auto const &entity : guis)
	{
		const Transform2DComponent &transformComponent = registry.get<Transform2DComponent>(entity);
		m_Shader.loadTransformationMatrix(
				Maths::createTransformationMatrix(glm::vec3{transformComponent.position, 0},
												  glm::vec3{transformComponent.scale, 0},
												  glm::vec3{transformComponent.rotation, 0}));

		glDrawElements(GL_TRIANGLES, texturedModel.vertexCount(), GL_UNSIGNED_INT, nullptr);
	}
}
