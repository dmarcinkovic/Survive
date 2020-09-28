//
// Created by david on 28. 03. 2020..
//

#include "GuiRenderer.h"
#include "../math/Maths.h"
#include "../renderer/Renderer2DUtil.h"

void GuiRenderer::render() const
{
    Renderer2DUtil::prepareRendering(m_Shader);

    for (auto const&[texture, batch] : m_Entities)
    {
        Renderer2DUtil::prepareEntity(texture);
        for (auto const &entity2D : batch)
        {
            const Entity &e = entity2D.get();
            m_Shader.loadTransformationMatrix(
                    Maths::createTransformationMatrix(e.m_Position, e.m_ScaleX, e.m_ScaleY));

            glDrawElements(GL_TRIANGLES, texture.vertexCount(), GL_UNSIGNED_INT, nullptr);
        }

        Renderer2DUtil::finishRenderingEntity();
    }

    Renderer2DUtil::finishRendering();
}

void GuiRenderer::addEntity(Entity &entity2D) noexcept
{
    std::vector<std::reference_wrapper<Entity>> &batch = m_Entities[entity2D.m_Texture];
    batch.emplace_back(entity2D);
}
