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