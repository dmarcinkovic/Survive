//
// Created by david on 29. 03. 2020..
//

#include "SpritesRenderer.h"
#include "../math/Maths.h"
#include "../renderer/RendererUtil.h"

void SpritesRenderer::renderSprite() const
{
    RendererUtil::prepareRendering(m_Shader);

    for (auto const&[texture, batch] : m_Sprites)
    {
        RendererUtil::prepareEntity(texture);
        for (auto const &sprite : batch)
        {
            m_Shader.loadTransformationMatrix(
                    Maths::createTransformationMatrix(sprite.get().m_Position, sprite.get().m_Scale));
            animate(sprite.get());

            glDrawElements(GL_TRIANGLES, texture.vertexCount(), GL_UNSIGNED_INT, nullptr);
        }

        RendererUtil::finishRenderingEntity();
    }

    RendererUtil::finishRendering();
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
