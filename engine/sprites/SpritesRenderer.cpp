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

			loadUniforms(transformComponent, spriteComponent);
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

void SpritesRenderer::loadUniforms(const TransformComponent &transform, const Sprite &sprite) const
{
	glm::mat4 modelMatrix = Maths::createTransformationMatrix(transform.position, transform.scale, transform.rotation);

	m_Shader.loadTransformationMatrix(modelMatrix);
	m_Shader.loadSpriteSize(sprite.row, sprite.col);
	m_Shader.loadSpritePosition(sprite.getFrameIndex());
}
