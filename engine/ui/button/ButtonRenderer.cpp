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
        RendererUtil::prepareEntity(button.get().getMEntity().m_Texture);

        const Entity2D &entity = button.get().getMEntity();
        m_Shader.loadTransformationMatrix(
                Maths::createTransformationMatrix(entity.m_Position, entity.m_ScaleX, entity.m_ScaleY));

        glDrawElements(GL_TRIANGLES, entity.m_Texture.vertexCount(), GL_UNSIGNED_INT, nullptr);

        RendererUtil::finishRenderingEntity();
    }

    RendererUtil::finishRendering();
}

void ButtonRenderer::addButton(Button &button)
{
    m_Buttons.emplace_back(button);
}
