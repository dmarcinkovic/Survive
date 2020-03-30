//
// Created by david on 29. 03. 2020..
//

#include "TextRenderer.h"

TextRenderer::TextRenderer(Loader &loader)
        : m_Model(loader.loadToVao(m_Vertices, m_TextureCoords, 2))
{

}

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

const Model &TextRenderer::getModel() const
{
    return m_Model;
}
