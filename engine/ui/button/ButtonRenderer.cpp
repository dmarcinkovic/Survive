//
// Created by david on 05. 05. 2020..
//


#include "ButtonRenderer.h"
#include "../../renderer/Renderer2DUtil.h"
#include "../../math/Maths.h"

void ButtonRenderer::render() const
{
    if (m_Buttons.empty()) return;

    Renderer2DUtil::prepareRendering(m_Shader);
    Renderer2DUtil::prepareEntity(m_Buttons[0].get().m_Texture);

    for (auto const &buttons : m_Buttons)
    {
        const Button &button = buttons.get();

        m_Shader.loadColor(button.m_Color);
        m_Shader.loadTransformationMatrix(
                Maths::createTransformationMatrix(button.m_Position, button.m_ScaleX, button.m_ScaleY));

        glDrawElements(GL_TRIANGLES, button.m_Texture.vertexCount(), GL_UNSIGNED_INT, nullptr);
    }

    Renderer2DUtil::finishRenderingEntity();
    Renderer2DUtil::finishRendering();
}

void ButtonRenderer::addButton(Button &button) noexcept
{
    m_Buttons.emplace_back(button);
}