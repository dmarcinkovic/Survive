//
// Created by david on 10. 02. 2021..
//

#include "ParticleTexture.h"

ParticleTexture::ParticleTexture(Texture texture, int numberOfRows)
	: m_Texture(texture), m_Rows(numberOfRows)
{

}

const Texture &ParticleTexture::getTexture() const
{
	return m_Texture;
}

int ParticleTexture::getRows() const
{
	return m_Rows;
}
