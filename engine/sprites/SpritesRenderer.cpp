//
// Created by david on 29. 03. 2020..
//

#include "SpritesRenderer.h"
#include "../math/Maths.h"
#include "../renderer/Renderer2DUtil.h"

void SpritesRenderer::renderSprite() const
{
    Renderer2DUtil::prepareRendering(m_Shader);

    for (auto const&[texture, batch] : m_Sprites)
    {
        Renderer2DUtil::prepareEntity(texture);
        for (auto const &sprite : batch)
        {
            auto &s = sprite.get();
            m_Shader.loadTransformationMatrix(
                    Maths::createTransformationMatrix(s.m_Position, s.m_ScaleX, s.m_ScaleY));
            animate(sprite.get());

            glDrawElements(GL_TRIANGLES, texture.vertexCount(), GL_UNSIGNED_INT, nullptr);
        }

        Renderer2DUtil::finishRenderingEntity();
    }

    Renderer2DUtil::finishRendering();
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
    m_Shader.loadSpritePosition(sprite.m_CurrentFrameIndex);
}
