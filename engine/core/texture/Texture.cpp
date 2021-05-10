//
// Created by david on 06. 06. 2020..
//

#include "Texture.h"

Survive::Texture::Texture(GLuint textureId)
		: m_TextureId(textureId)
{

}

void Survive::Texture::bindTexture(int textureIndex) const
{
	glActiveTexture(GL_TEXTURE0 + textureIndex);
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
}

void Survive::Texture::unbindTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Survive::Texture::textureId() const
{
	return m_TextureId;
}

void Survive::Texture::bindCubeTexture(int textureIndex) const
{
	glActiveTexture(GL_TEXTURE0 + textureIndex);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureId);
}

void Survive::Texture::unbindCubeTexture()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

bool Survive::Texture::isValidTexture() const
{
	return m_TextureId != 0;
}
