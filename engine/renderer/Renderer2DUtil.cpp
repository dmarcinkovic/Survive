//
// Created by david on 03. 05. 2020..
//

#include "Renderer2DUtil.h"

void Renderer2DUtil::prepareRendering(const Shader &shader)
{
    shader.start();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
}

void Renderer2DUtil::finishRendering()
{
    Shader::stop();
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}

void Renderer2DUtil::prepareEntity(const Texture &texture)
{
    texture.bindTexture();
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

void Renderer2DUtil::finishRenderingEntity()
{
    Texture::unbindTexture();

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    Loader::unbindVao();
}
