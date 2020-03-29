//
// Created by david on 29. 03. 2020..
//

#include "TextRenderer.h"

void TextRenderer::renderText() const
{
    prepareRendering(m_Shader);

    for (auto const&[texture, batch] : m_Texts)
    {
        prepareEntity(texture);
        for (auto const &entity2D : batch)
        {
            // TODO draw text
//            glDrawElements(GL_TRIANGLES, texture.vertexCount(), GL_UNSIGNED_INT, nullptr);
        }

        finishRenderingEntity();
    }

    finishRendering();
}

void TextRenderer::addText(Text &text)
{

}
