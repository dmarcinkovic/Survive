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
        for (auto const &text : batch)
        {
            m_Shader.loadColor(text.get().color());
            glDrawArrays(GL_TRIANGLES, 0, texture.vertexCount());
        }

        finishRenderingEntity();
    }

    finishRendering();
}

void TextRenderer::addText(Text &text)
{
    auto &texts = m_Texts[text.m_Texture];
    texts.emplace_back(text);
}
