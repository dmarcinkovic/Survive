//
// Created by david on 28. 03. 2020..
//

#include "GuiRenderer.h"
#include "../math/Maths.h"
#include "../renderer/RendererUtil.h"

void GuiRenderer::renderGui() const
{
    RendererUtil::prepareRendering(m_Shader);

    for (auto const&[texture, batch] : m_Guis)
    {
        RendererUtil::prepareEntity(texture);
        for (auto const &entity2D : batch)
        {
            m_Shader.loadTransformationMatrix(
                    Maths::createTransformationMatrix(entity2D.m_Position, entity2D.m_Scale));
            glDrawElements(GL_TRIANGLES, texture.vertexCount(), GL_UNSIGNED_INT, nullptr);
        }

        RendererUtil::finishRenderingEntity();
    }

    RendererUtil::finishRendering();
}

void GuiRenderer::addGui(const Entity2D &entity2D) noexcept
{
    std::vector<Entity2D> &batch = m_Guis[entity2D.m_Texture];

    batch.emplace_back(entity2D);
}
