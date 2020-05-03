//
// Created by david on 29. 03. 2020..
//

#include "TextRenderer.h"
#include "../renderer/RendererUtil.h"

void TextRenderer::renderText() const
{
    RendererUtil::prepareRendering(m_Shader);

    for (auto const&[texture, batch] : m_Texts)
    {
        RendererUtil ::prepareEntity(texture);
        for (auto const &text : batch)
        {
            m_Shader.loadColor(text.get().color());
            glDrawArrays(GL_TRIANGLES, 0, texture.vertexCount());
        }

        RendererUtil::finishRenderingEntity();
    }

    RendererUtil::finishRendering();
}

void TextRenderer::addText(Text &text)
{
    auto &texts = m_Texts[text.m_Texture];
    texts.emplace_back(text);
}
