//
// Created by david on 03. 05. 2020..
//

#include "ButtonRenderer.h"
#include "../../renderer/RendererUtil.h"
#include "../../math/Maths.h"

void ButtonRenderer::render() const
{
    RendererUtil::prepareRendering(m_Shader);

    for (auto const &button : m_Buttons)
    {
        RendererUtil::prepareEntity(button.get().m_Texture);

        glDrawElements(GL_TRIANGLES, button.get().m_Texture.vertexCount(), GL_UNSIGNED_INT, nullptr);

        RendererUtil::finishRenderingEntity();
    }

    RendererUtil::finishRendering();
}

void ButtonRenderer::addButton(Button &button)
{
    loadUniforms(button);

    m_Buttons.emplace_back(button);
}

void ButtonRenderer::loadUniforms(Button &button) const
{
    m_Shader.start();

    m_Shader.loadColor(button.m_Color);
    m_Shader.loadTransformationMatrix(
            Maths::createTransformationMatrix(button.m_Position, button.m_ScaleX, button.m_ScaleY));

    Shader::stop();
}
