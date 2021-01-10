//
// Created by david on 17. 05. 2020..
//

#include "Object3D.h"

Object3D::Object3D(const TexturedModel &texture, const glm::vec3 &position, const glm::vec3 &rotation,
				   bool isTransparent, const glm::vec3 &scale)
		: Entity(texture, position, scale), m_Rotation(rotation), m_IsTransparent(isTransparent)
{

}

void Object3D::addBloomEffect(const Texture &bloomTexture, float bloomStrength)
{
	m_BloomTexture = bloomTexture;
	m_BloomStrength = bloomStrength;
}

const Texture &Object3D::getBloomTexture() const
{
	return m_BloomTexture;
}

float Object3D::getBloomStrength() const
{
	return m_BloomStrength;
}
