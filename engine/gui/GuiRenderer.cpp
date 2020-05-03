//
// Created by david on 28. 03. 2020..
//

#include "GuiRenderer.h"
#include "../math/Maths.h"
#include "../renderer/RendererUtil.h"

void GuiRenderer::render() const
{
    RendererUtil::prepareRendering(m_Shader);

    for (auto const&[texture, batch] : m_Entities)
    {
        RendererUtil::prepareEntity(texture);
        for (auto const &entity2D : batch)
        {
            const Entity2D &e = entity2D.get();
            m_Shader.loadTransformationMatrix(
                    Maths::createTransformationMatrix(e.m_Position, e.m_ScaleX));

            glDrawElements(GL_TRIANGLES, texture.vertexCount(), GL_UNSIGNED_INT, nullptr);
        }

        RendererUtil::finishRenderingEntity();
    }

    RendererUtil::finishRendering();
}

void GuiRenderer::addEntity(Entity2D &entity2D) noexcept
{
    std::vector<std::reference_wrapper<Entity2D>> &batch = m_Entities[entity2D.m_Texture];

    batch.emplace_back(entity2D);
}
