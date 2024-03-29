//
// Created by david on 29. 03. 2020..
//

#include "SpritesRenderer.h"
#include "Renderer2D.h"
#include "Maths.h"

void Survive::SpritesRenderer::render(entt::registry &registry, const Camera &camera) const
{
	constexpr int numberOfVertexUnits = 1;
	auto entities = prepareEntities(registry);

	if (entities.empty())
	{
		return;
	}

	prepareRendering(m_Shader);
	m_Shader.loadProjectionMatrix(camera.getOrthographicProjectionMatrix());

	for (auto const&[texture, sprites] : entities)
	{
		prepareEntity(texture, numberOfVertexUnits);
		renderSprites(sprites, registry, texture);

		finishRenderingEntity(numberOfVertexUnits);
	}

	finishRendering();
}

void
Survive::SpritesRenderer::loadUniforms(const Transform3DComponent &transform, const SpriteSheetComponent &sprite) const
{
	glm::mat4 modelMatrix = Maths::createTransformationMatrix(transform.position, transform.scale, transform.rotation);

	m_Shader.loadTransformationMatrix(modelMatrix);
	m_Shader.loadSpriteSize(sprite.row, sprite.col);
	m_Shader.loadSpritePosition(sprite.currentFrameIndex);
}

std::unordered_map<Survive::TexturedModel, std::vector<entt::entity>, Survive::TextureHash>
Survive::SpritesRenderer::prepareEntities(entt::registry &registry)
{
	auto group = registry.view<Render2DComponent, Transform3DComponent, SpriteSheetComponent, TagComponent>();

	std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash> entities;
	for (auto const &entity : group)
	{
		const Render2DComponent &renderComponent = group.get<Render2DComponent>(entity);

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
		const Transform3DComponent &transformComponent = registry.get<Transform3DComponent>(sprite);
		const SpriteSheetComponent &spriteComponent = registry.get<SpriteSheetComponent>(sprite);

		loadUniforms(transformComponent, spriteComponent);

		glDrawElements(GL_TRIANGLES, texturedModel.vertexCount(), GL_UNSIGNED_INT, nullptr);
	}
}
