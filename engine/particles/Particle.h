//
// Created by david on 05. 02. 2021..
//

#ifndef SURVIVE_PARTICLE_H
#define SURVIVE_PARTICLE_H


#include <glm/vec2.hpp>
#include "../entity/Entity.h"
#include "../camera/Camera.h"

class Particle : public Entity
{
private:
	glm::vec3 m_Velocity{};
	glm::vec3 m_Rotation{};

	float m_BlendFactor{};
	int m_Rows;

	float m_GravityEffect{};
	float m_LifeLength{};

	float m_ElapsedTime{};

	glm::vec2 m_TextureOffset1{};
	glm::vec2 m_TextureOffset2{};

	float m_Distance{};

public:
	Particle(const TexturedModel &particleTexture, int rows, const glm::vec3 &position, const glm::vec3 &velocity,
			 float gravityEffect, float lifeLength, float rotation = 0.0f, float scale = 1.0f);

	bool update(const Camera &camera);

private:
	void updateTextureCoordInfo();

	[[nodiscard]] glm::vec2 setTextureOffset(int index) const;

	[[nodiscard]] float getAtlasProgression(int stageCount) const;

	void updateTextureOffsets(float atlasProgression, int stageCount);

	void applyGravity();

	void updateTimeElapsed();

	friend class ParticleRenderer;
};


#endif //SURVIVE_PARTICLE_H
