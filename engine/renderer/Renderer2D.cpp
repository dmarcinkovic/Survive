//
// Created by david on 27. 03. 2020..
//

#include "Renderer2D.h"

Renderer2D::Renderer2D(const Shader &shader)
        : m_Shader(shader)
{

}

void Renderer2D::render(const std::vector<Entity2D> &entities)
{
    for (auto const &entity2D : entities)
    {
        prepareRendering(entity2D);

        glDrawElements(GL_TRIANGLES, entity2D.m_Texture.vertexCount(), GL_UNSIGNED_INT, nullptr);

        finishRendering();
    }
}

void Renderer2D::prepareRendering(const Entity2D &entity2D)
{
    m_Shader.start();
    entity2D.m_Texture.bindTexture();

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

void Renderer2D::finishRendering()
{
    Shader::stop();
    Texture::unbindTexture();

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    Loader::unbindVao();
}
