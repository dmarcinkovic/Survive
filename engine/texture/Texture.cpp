//
// Created by david on 24. 03. 2020..
//

#include "Texture.h"

Texture::Texture(const Model &model, GLuint textureId)
    : m_Vao(model.vao), m_TextureID(textureId), m_VertexCount(model.vertexCount)
{

}

void Texture::bindTexture() const
{
    glBindVertexArray(m_Vao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void Texture::unbindTexture()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
