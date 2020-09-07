//
// Created by david on 29. 03. 2020..
//


#include "TextRenderer.h"
#include "../renderer/Renderer2DUtil.h"

void TextRenderer::renderText() const
{
    Renderer2DUtil::prepareRendering(m_Shader);

    for (auto const&[texture, batch] : m_Texts)
    {
        Renderer2DUtil ::prepareEntity(texture);
        for (auto const &text : batch)
        {
            m_Shader.loadColor(text.get().color());
            m_Shader.loadBorder(text.get().getMBorderColor(), text.get().getMBorderWidth());

            glDrawArrays(GL_TRIANGLES, 0, text.get().m_Texture.vertexCount());
        }

        Renderer2DUtil::finishRenderingEntity();
    }

    Renderer2DUtil::finishRendering();
}

void TextRenderer::addText(Text &text, Loader &loader)
{
    text.loadTexture(loader);
    auto &texts = m_Texts[text.m_Texture];
    texts.emplace_back(text);
}
