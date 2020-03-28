//
// Created by david on 28. 03. 2020..
//

#include "GuiRenderer.h"
#include "../../math/Maths.h"

void GuiRenderer::render()
{
    m_Shader.start();
    for (auto const&[texture, batch] : entities)
    {
        prepareRendering(texture);

        for (auto const &entity2D : batch)
        {
            glDrawElements(GL_TRIANGLES, texture.vertexCount(), GL_UNSIGNED_INT, nullptr);
        }

        finishRendering();
    }
    Shader::stop();
}

void GuiRenderer::prepareRendering(const Texture &texture) const
{
    texture.bindTexture();
    m_Shader.loadTransformationMatrix(
            Maths::createTransformationMatrix(glm::vec3{-0.5, 0.5, 0}, 0.3));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

void GuiRenderer::finishRendering()
{
    Texture::unbindTexture();

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    Loader::unbindVao();
}

void GuiRenderer::addEntity(const Entity2D &entity2D) noexcept
{
    std::vector<Entity2D> &batch = entities[entity2D.m_Texture];

    batch.emplace_back(entity2D);
}
