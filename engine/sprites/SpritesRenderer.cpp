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
        for (auto const &sprite : batch)
        {
            m_Shader.loadTransformationMatrix(
                    Maths::createTransformationMatrix(sprite.m_Position, sprite.m_Scale));
            glDrawElements(GL_TRIANGLES, texture.vertexCount(), GL_UNSIGNED_INT, nullptr);
        }

        finishRenderingEntity();
    }

    finishRendering();
}

void SpritesRenderer::addSprite(const Sprite &sprite) noexcept
{
    std::vector<Sprite> &batch = m_Sprites[sprite.m_Texture];

    batch.emplace_back(sprite);
}
