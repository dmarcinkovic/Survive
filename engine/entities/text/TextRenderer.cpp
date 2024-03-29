//
// Created by david on 29. 03. 2020..
//

#include "TextRenderer.h"
#include "Components.h"
#include "Maths.h"
#include "Renderer2D.h"

void Survive::TextRenderer::renderText(entt::registry &registry, const Camera &camera) const
{
	auto texts = registry.view<Transform3DComponent, TextComponent, SpriteComponent, TagComponent>();

	if (texts.begin() == texts.end())
	{
		return;
	}

	prepareRendering(m_Shader);
	m_Shader.loadProjectionMatrix(camera.getOrthographicProjectionMatrix());

	for (auto const &text: texts)
	{
		const TexturedModel &model = texts.get<TextComponent>(text).text.getModel();
		prepareEntity(model);

		loadUniforms(registry, text);

		glDrawArrays(GL_TRIANGLES, 0, model.vertexCount());

		finishRenderingEntity();
	}

	finishRendering();
}

void Survive::TextRenderer::loadUniforms(entt::registry &registry, entt::entity entity) const
{
	const SpriteComponent &spriteComponent = registry.get<SpriteComponent>(entity);
	m_Shader.loadColor(glm::vec3{spriteComponent.color});

	const TextComponent &textComponent = registry.get<TextComponent>(entity);
	m_Shader.loadBorder(textComponent.text.getBorderColor(), textComponent.text.getBorderWidth());

	const Transform3DComponent &transformComponent = registry.get<Transform3DComponent>(entity);
	glm::mat4 modelMatrix = Maths::createTransformationMatrix(transformComponent.position, transformComponent.scale,
															  transformComponent.rotation);
	m_Shader.loadTransformationMatrix(modelMatrix);
}
