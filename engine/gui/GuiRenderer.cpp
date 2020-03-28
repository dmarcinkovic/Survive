//
// Created by david on 28. 03. 2020..
//

#include "GuiRenderer.h"

void GuiRenderer::render(const Entity2D &entity2D)
{
    prepareRendering(entity2D);

    glDrawElements(GL_TRIANGLES, entity2D.m_Texture.vertexCount(), GL_UNSIGNED_INT, nullptr);

    finishRendering();
}

void GuiRenderer::prepareRendering(const Entity2D &entity2D) const
{
    m_Shader.start();
    entity2D.m_Texture.bindTexture();

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

void GuiRenderer::finishRendering()
{
    Shader::stop();
    Texture::unbindTexture();

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    Loader::unbindVao();
}
