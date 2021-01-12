//
// Created by david on 17. 05. 2020..
//

#ifndef SURVIVE_OBJECT3D_H
#define SURVIVE_OBJECT3D_H

#include "../entity/Entity.h"

struct Object3D : public Entity
{
	static int id;

	glm::vec3 m_Rotation;
	bool m_IsTransparent;
	Texture m_Skybox;

	float m_ReflectiveFactor{};
	float m_RefractionFactor{};
	float m_RefractiveIndex{};

	bool m_DrawOutline{};
	int m_Id{};

	Object3D(const TexturedModel &texture, const glm::vec3 &position, const glm::vec3 &rotation = glm::vec3{0, 0, 0},
			 bool isTransparent = false, const glm::vec3 &scale = glm::vec3{1.0f, 1.0f, 1.0f});

	void addBloomEffect(const Texture &bloomTexture, float bloomStrength = 3.0f);

	[[nodiscard]] const Texture &getBloomTexture() const;

	[[nodiscard]] float getBloomStrength() const;

private:
	Texture m_BloomTexture{};
	float m_BloomStrength{};

};


#endif //SURVIVE_OBJECT3D_H
