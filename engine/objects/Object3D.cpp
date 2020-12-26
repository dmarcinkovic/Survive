//
// Created by david on 17. 05. 2020..
//

#include "Object3D.h"

Object3D::Object3D(const TexturedModel &texture, const Texture &skybox, const glm::vec3 &position,
				   const glm::vec3 &rotation,
				   bool isTransparent, float scaleX, float scaleY, float scaleZ)
		: Entity(texture, position, scaleX, scaleY, scaleZ), m_Skybox(skybox), m_Rotation(rotation),
		  m_IsTransparent(isTransparent)
{

}