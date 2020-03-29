//
// Created by david on 29. 03. 2020..
//

#include "SpritesRenderer.h"
#include "../math/Maths.h"

void SpritesRenderer::renderSprite() const
{
    prepareRendering(m_Shader);

    for (auto const&[texture, batch] : m_Sprites)
    {
        prepareEntity(texture);
        for (auto const &entity2D : batch)
        {
            m_Shader.loadTransformationMatrix(
                    Maths::createTransformationMatrix(entity2D.m_Position, entity2D.m_Scale));
            glDrawElements(GL_TRIANGLES, texture.vertexCount(), GL_UNSIGNED_INT, nullptr);
        }

        finishRenderingEntity();
    }

    finishRendering();
}

void SpritesRenderer::addSprite(const Entity2D &entity2D) noexcept
{
    std::vector<Entity2D> &batch = m_Sprites[entity2D.m_Texture];

    batch.emplace_back(entity2D);
}
