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
            Sprite &s = sprite.get();
            m_Shader.loadTransformationMatrix(
                    Maths::createTransformationMatrix(sprite.get().m_Position, sprite.get().m_Scale));
            animate(s);

            glDrawElements(GL_TRIANGLES, texture.vertexCount(), GL_UNSIGNED_INT, nullptr);
        }

        finishRenderingEntity();
    }

    finishRendering();
}

void SpritesRenderer::addSprite(Sprite &sprite) noexcept
{
    std::vector<std::reference_wrapper<Sprite>> &batch = m_Sprites[sprite.m_Texture];

    batch.emplace_back(sprite);
}

void SpritesRenderer::animate(Sprite &sprite) const
{
    if (sprite.m_Animate)
    {
        sprite.animate();
    }

    m_Shader.loadSpriteSize(sprite.m_Row, sprite.m_Col);
    m_Shader.loadSpritePosition(sprite.m_CurrentRow, sprite.m_CurrentCol);
}
