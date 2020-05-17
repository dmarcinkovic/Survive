//
// Created by david on 17. 05. 2020..
//

#include "Renderer3DUtil.h"

void Renderer3DUtil::prepareRendering(const Shader &shader, bool cullFace, bool blend)
{
    shader.start();
    glEnable(GL_DEPTH_TEST);

    if (cullFace)
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }

    if (blend)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
}

void Renderer3DUtil::finishRendering()
{
    Shader::stop();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_BLEND);
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
