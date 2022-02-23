//
// Created by david on 05. 05. 2020..
//

#include "ButtonRenderer.h"
#include "Maths.h"
#include "Renderer2D.h"

void Survive::ButtonRenderer::render() const
{
	if (m_Buttons.empty())
	{
		return;
	}

	prepareRendering(m_Shader);

	for (auto const &buttons : m_Buttons)
	{
		const Button &button = buttons.get();
		prepareEntity(button.m_Texture);

		m_Shader.loadColor(button.m_Color);
		m_Shader.loadTransformationMatrix(
				Maths::createTransformationMatrix(button.m_Position, button.m_Scale));

		m_Shader.loadIsLoadingImage(button.m_Texture.isValidTexture());

		glDrawElements(GL_TRIANGLES, button.m_Texture.vertexCount(), GL_UNSIGNED_INT, nullptr);
		finishRenderingEntity();
	}

	finishRendering();
}

void Survive::ButtonRenderer::addButton(Button &button) noexcept
{
	m_Buttons.emplace_back(button);
}
