//
// Created by david on 17. 05. 2020..
//

#include "Object3D.h"

int Object3D::id = 1;

Object3D::Object3D(const TexturedModel &texture, const glm::vec3 &position, const glm::vec3 &rotation,
				   bool isTransparent, const glm::vec3 &scale)
		: Entity(texture, position, scale), m_Rotation(rotation), m_IsTransparent(isTransparent)
{
	m_Id = id++;
}

void Object3D::addBloomEffect(const Texture &emissiveTexture, float bloomStrength)
{
	m_EmissiveTexture = emissiveTexture;
	m_BloomStrength = bloomStrength;
}

const Texture &Object3D::getEmissiveTexture() const
{
	return m_EmissiveTexture;
}

float Object3D::getBloomStrength() const
{
	return m_BloomStrength;
}

void Object3D::addBloomTexture(const Texture &bloomTexture)
{
	m_BloomTexture = bloomTexture;
}

const Texture &Object3D::getBloomTexture() const
{
	return m_BloomTexture;
}
