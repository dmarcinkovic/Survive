//
// Created by david on 17. 05. 2020..
//

#ifndef SURVIVE_OBJECT3D_H
#define SURVIVE_OBJECT3D_H

#include "../entity/Entity.h"

struct Object3D : public Entity
{
	glm::vec3 m_Rotation;
	bool m_IsTransparent;
	Texture m_Skybox;

	float m_ReflectiveFactor{};
	float m_RefractionFactor{};
	float m_RefractiveIndex{};

	bool m_DrawOutline{};
	Texture m_BloomTexture{};

	Object3D(const TexturedModel &texture, const glm::vec3 &position, const glm::vec3 &rotation = glm::vec3{0, 0, 0},
			 bool isTransparent = false, const glm::vec3 &scale = glm::vec3{1.0f, 1.0f, 1.0f});
};


#endif //SURVIVE_OBJECT3D_H
