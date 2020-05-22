//
// Created by david on 17. 05. 2020..
//

#include "Renderer3DUtil.h"

void Renderer3DUtil::prepareRendering(const Shader &shader)
{
    shader.start();
    glEnable(GL_DEPTH_TEST);
}

void Renderer3DUtil::finishRendering()
{
    Shader::stop();
    glDisable(GL_DEPTH_TEST);
}

void Renderer3DUtil::prepareEntity(const Texture &texture)
{
    texture.bindTexture();
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
}

void Renderer3DUtil::finishRenderingEntity()
{
    Texture::unbindTexture();
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    Loader::unbindVao();
}

void Renderer3DUtil::addTransparency(bool cullFace, bool blend)
{
    if (cullFace)
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    } else
    {
        glDisable(GL_CULL_FACE);
    }

    if (blend)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    } else
    {
        glDisable(GL_BLEND);
    }
}
