//
// Created by david on 29. 03. 2020..
//

#include <iostream>
#include "TextRenderer.h"
#include "../renderer/RendererUtil.h"
#include "../math/Maths.h"

void TextRenderer::renderText() const
{
    RendererUtil::prepareRendering(m_Shader);

    for (auto const&[texture, batch] : m_Texts)
    {
        RendererUtil::prepareEntity(texture);
        for (auto const &text : batch)
        {
            m_Shader.loadColor(text.get().color());
            m_Shader.loadBorder(text.get().getMBorderColor(), text.get().getMBorderWidth());

            float scale = text.get().getScale();
            m_Shader.loadTransformationMatrix(
                    Maths::createTransformationMatrix(glm::vec3{}, scale, scale));
            glDrawArrays(GL_TRIANGLES, 0, texture.vertexCount());
        }

        RendererUtil::finishRenderingEntity();
    }

    RendererUtil::finishRendering();
}

void TextRenderer::addText(Text &text, Loader &loader)
{
    text.loadTexture(loader);
    auto &texts = m_Texts[text.m_Texture];
    texts.emplace_back(text);
}
