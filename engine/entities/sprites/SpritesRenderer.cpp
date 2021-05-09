//
// Created by david on 29. 03. 2020..
//

#include "SpritesRenderer.h"
#include "RenderComponent.h"
#include "Maths.h"
#include "Renderer2DUtil.h"


void Survive::SpritesRenderer::render(entt::registry &registry) const
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

void
Survive::SpritesRenderer::loadUniforms(const Transform2DComponent &transform, const SpriteSheetComponent &sprite) const
{
	glm::mat4 modelMatrix = Maths::createTransformationMatrix(glm::vec3{transform.position, 0},
															  glm::vec3{transform.scale, 0},
															  glm::vec3{transform.rotation, 0});

	m_Shader.loadTransformationMatrix(modelMatrix);
	m_Shader.loadSpriteSize(sprite.row, sprite.col);
	m_Shader.loadSpritePosition(sprite.currentFrameIndex);
}

std::unordered_map<Survive::TexturedModel, std::vector<entt::entity>, Survive::TextureHash>
Survive::SpritesRenderer::prepareEntities(entt::registry &registry)
{
	auto group = registry.group<RenderComponent, Transform2DComponent, SpriteSheetComponent>();

	std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash> entities;
	for (auto const &entity : group)
	{
		const RenderComponent &renderComponent = group.get<RenderComponent>(entity);

		std::vector<entt::entity> &batch = entities[renderComponent.texturedModel];
		batch.emplace_back(entity);
	}

	return entities;
}

void Survive::SpritesRenderer::renderSprites(const std::vector<entt::entity> &sprites, const entt::registry &registry,
											 const TexturedModel &texturedModel) const
{
	for (auto const &sprite : sprites)
	{
		const Transform2DComponent &transformComponent = registry.get<Transform2DComponent>(sprite);
		const SpriteSheetComponent &spriteComponent = registry.get<SpriteSheetComponent>(sprite);

		loadUniforms(transformComponent, spriteComponent);

		glDrawElements(GL_TRIANGLES, texturedModel.vertexCount(), GL_UNSIGNED_INT, nullptr);
	}
}