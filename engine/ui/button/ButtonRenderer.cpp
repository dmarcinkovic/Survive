//
// Created by david on 05. 05. 2020..
//


#include <iostream>
#include "ButtonRenderer.h"
#include "../../renderer/RendererUtil.h"
#include "../../math/Maths.h"

void ButtonRenderer::render() const
{
    if (m_Buttons.empty()) return;

    RendererUtil::prepareRendering(m_Shader);
    RendererUtil::prepareEntity(m_Buttons[0].get().m_Texture);

    for (auto const &buttons : m_Buttons)
    {
        const Button &button = buttons.get();

        m_Shader.loadColor(button.m_Color);
        m_Shader.loadTransformationMatrix(
                Maths::createTransformationMatrix(button.m_Position, button.m_ScaleX, button.m_ScaleY));

        m_Shader.loadIsLoadingImage(button.m_Texture.isValidTexture());

        glDrawElements(GL_TRIANGLES, button.m_Texture.vertexCount(), GL_UNSIGNED_INT, nullptr);
    }

    RendererUtil::finishRenderingEntity();
    RendererUtil::finishRendering();
}

void ButtonRenderer::addButton(Button &button) noexcept
{
    m_Buttons.emplace_back(button);
}
