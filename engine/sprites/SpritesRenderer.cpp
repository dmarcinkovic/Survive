//
// Created by david on 29. 03. 2020..
//

#include "SpritesRenderer.h"
#include "../math/Maths.h"
#include "../renderer/Renderer2DUtil.h"
#include "../components/RenderComponent.h"
#include "../components/TransformComponent.h"

void SpritesRenderer::renderSprite(entt::registry &registry) const
{
	if (m_Sprites.empty())
	{
		return;
	}

	Renderer2DUtil::prepareRendering(m_Shader);

	for (auto const&[texture, entities] : m_Sprites)
	{
		Renderer2DUtil::prepareEntity(texture);
		for (auto const &sprite : entities)
		{
			TransformComponent transformComponent = registry.get<TransformComponent>(sprite);
			Sprite &spriteComponent = registry.get<Sprite>(sprite);

			m_Shader.loadTransformationMatrix(
					Maths::createTransformationMatrix(transformComponent.position, transformComponent.scale));
			m_Shader.loadSpriteSize(spriteComponent.row, spriteComponent.col);
			m_Shader.loadSpritePosition(spriteComponent.getFrameIndex());

			animate(spriteComponent);

			glDrawElements(GL_TRIANGLES, texture.vertexCount(), GL_UNSIGNED_INT, nullptr);
		}

		Renderer2DUtil::finishRenderingEntity();
	}

	Renderer2DUtil::finishRendering();
}

void SpritesRenderer::addSprite(const entt::registry &registry, entt::entity entity) noexcept
{
	RenderComponent renderComponent = registry.get<RenderComponent>(entity);

	std::vector<entt::entity> &batch = m_Sprites[renderComponent.texturedModel];
	batch.emplace_back(entity);
}

void SpritesRenderer::animate(Sprite &sprite)
{
	sprite.update();
}
