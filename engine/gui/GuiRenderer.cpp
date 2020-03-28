//
// Created by david on 28. 03. 2020..
//

#include "GuiRenderer.h"
#include "../../math/Maths.h"

void GuiRenderer::render() const
{
    prepareRendering();

    for (auto const&[texture, batch] : m_Entities)
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

void GuiRenderer::prepareRendering() const
{
    m_Shader.start();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GuiRenderer::finishRendering()
{
    Shader::stop();
    glDisable(GL_BLEND);
}

void GuiRenderer::addEntity(const Entity2D &entity2D) noexcept
{
    std::vector<Entity2D> &batch = m_Entities[entity2D.m_Texture];

    batch.emplace_back(entity2D);
}

void GuiRenderer::prepareEntity(const Texture &texture) const
{
    texture.bindTexture();
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

void GuiRenderer::finishRenderingEntity()
{
    Texture::unbindTexture();

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    Loader::unbindVao();
}
