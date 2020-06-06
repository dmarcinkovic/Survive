//
// Created by david on 06. 06. 2020..
//

#include "Texture.h"

Texture::Texture(GLuint textureId)
    : m_TextureId(textureId)
{

}

void Texture::bindTexture(int textureIndex) const
{
    glActiveTexture(GL_TEXTURE0 + textureIndex);
    glBindTexture(GL_TEXTURE_2D, m_TextureId);
}

void Texture::unbindTexture()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::textureId() const
{
    return m_TextureId;
}
