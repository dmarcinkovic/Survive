//
// Created by david on 24. 03. 2020..
//

#include "Texture.h"

Texture::Texture(const Model &model, GLuint textureId)
        : m_Vao(model.m_Vao), m_TextureID(textureId), m_VertexCount(model.m_VertexCount)
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

size_t Texture::vertexCount() const
{
    return m_VertexCount;
}

bool Texture::operator==(const Texture &rhs) const
{
    return m_Vao == rhs.m_Vao &&
           m_VertexCount == rhs.m_VertexCount &&
           m_TextureID == rhs.m_TextureID;
}

bool Texture::isValidTexture() const
{
    return m_TextureID != 0;
}
