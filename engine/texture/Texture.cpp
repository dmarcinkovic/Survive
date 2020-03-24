//
// Created by david on 24. 03. 2020..
//

#include "Texture.h"

Texture::Texture(const Model &model, GLuint textureId)
    : vao(model.vao), textureId(textureId), vertexCount(model.vertexCount)
{

}

void Texture::bindTexture()
{
    glBindVertexArray(vao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
}

void Texture::unbindTexture()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
