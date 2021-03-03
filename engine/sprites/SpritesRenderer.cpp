//
// Created by david on 29. 03. 2020..
//

#include "SpritesRenderer.h"
#include "../math/Maths.h"
#include "../renderer/Renderer2DUtil.h"
#include "../components/RenderComponent.h"


void SpritesRenderer::render(entt::registry &registry) const
{
	auto entities = prepareEntities(registry);

	if (entities.empty())
	{
		return;
	}

	Renderer2DUtil::prepareRendering(m_Shader);

	for (auto const&[texture, sprites] : entities)
	{
		Renderer2DUtil::prepareEntity(texture);
		renderSprites(sprites, registry, texture);

		Renderer2DUtil::finishRenderingEntity();
	}

	Renderer2DUtil::finishRendering();
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

std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash>
SpritesRenderer::prepareEntities(entt::registry &registry)
{
	auto group = registry.group<RenderComponent, TransformComponent, Sprite>();

	std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash> entities;
	for (auto const &entity : group)
	{
		RenderComponent renderComponent = group.get<RenderComponent>(entity);

		std::vector<entt::entity> &batch = entities[renderComponent.texturedModel];
		batch.emplace_back(entity);
	}

	return entities;
}

void SpritesRenderer::renderSprites(const std::vector<entt::entity> &sprites, entt::registry &registry,
									const TexturedModel &texturedModel) const
{
	for (auto const &sprite : sprites)
	{
		TransformComponent transformComponent = registry.get<TransformComponent>(sprite);
		Sprite &spriteComponent = registry.get<Sprite>(sprite);

		loadUniforms(transformComponent, spriteComponent);
		animate(spriteComponent);

		glDrawElements(GL_TRIANGLES, texturedModel.vertexCount(), GL_UNSIGNED_INT, nullptr);
	}
}
