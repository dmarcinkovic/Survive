//
// Created by david on 28. 03. 2020..
//

#include "GuiRenderer.h"
#include "../math/Maths.h"
#include "../renderer/Renderer2DUtil.h"
#include "../display/Display.h"
#include "../components/RenderComponent.h"
#include "../components/TransformComponent.h"

void GuiRenderer::render(const entt::registry &registry) const
{
	if (m_Entities.empty())
	{
		return;
	}

	Renderer2DUtil::prepareRendering(m_Shader);

	m_Shader.loadProjectionMatrix(Maths::orthographicProjectionMatrix);

	for (auto const&[texture, entities] : m_Entities)
	{
		Renderer2DUtil::prepareEntity(texture);
		for (auto const &entity : entities)
		{
			TransformComponent transformComponent = registry.get<TransformComponent>(entity);
			m_Shader.loadTransformationMatrix(
					Maths::createTransformationMatrix(transformComponent.position, transformComponent.scale,
													  transformComponent.rotation));

			glDrawElements(GL_TRIANGLES, texture.vertexCount(), GL_UNSIGNED_INT, nullptr);
		}

		Renderer2DUtil::finishRenderingEntity();
	}

	Renderer2DUtil::finishRendering();
}

void GuiRenderer::addEntity(const entt::registry &registry, entt::entity entity) noexcept
{
	RenderComponent renderComponent = registry.get<RenderComponent>(entity);

	std::vector<entt::entity> &batch = m_Entities[renderComponent.texturedModel];
	batch.emplace_back(entity);
}
