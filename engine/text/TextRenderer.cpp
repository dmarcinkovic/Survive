//
// Created by david on 29. 03. 2020..
//


#include "TextRenderer.h"
#include "../core/math/Maths.h"
#include "../core/renderer/Renderer2DUtil.h"

void Survive::TextRenderer::renderText() const
{
	if (m_Texts.empty())
	{
		return;
	}

	Renderer2DUtil::prepareRendering(m_Shader);

	for (auto const&[texture, batch] : m_Texts)
	{
		Renderer2DUtil::prepareEntity(texture);
		for (auto const &text : batch)
		{
			m_Shader.loadColor(text.get().color());
			m_Shader.loadBorder(text.get().getMBorderColor(), text.get().getMBorderWidth());

			float scale = text.get().getScale();
			m_Shader.loadTransformationMatrix(
					Maths::createTransformationMatrix(glm::vec3{}, glm::vec3{scale, scale, 1.0f}));

			glDrawArrays(GL_TRIANGLES, 0, text.get().m_Texture.vertexCount());
		}

		Renderer2DUtil::finishRenderingEntity();
	}

	Renderer2DUtil::finishRendering();
}

void Survive::TextRenderer::addText(Text &text, Loader &loader)
{
	text.loadTexture(loader);
	auto &texts = m_Texts[text.m_Texture];
	texts.emplace_back(text);
}
