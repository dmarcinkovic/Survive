//
// Created by david on 13. 02. 2021..
//

#ifndef SURVIVE_PARTICLESYSTEM_H
#define SURVIVE_PARTICLESYSTEM_H


#include <glm/vec3.hpp>
#include "../texture/TexturedModel.h"
#include "Particle.h"

class ParticleSystem
{
private:
	TexturedModel m_Texture;

	float m_ParticlesPerSecond;
	float m_Speed;
	float m_Gravity;
	float m_LifeLength;

public:
	ParticleSystem(const TexturedModel &particleTexture, float particlesPerSecond, float speed, float gravity,
				   float lifeLength);

	void generateParticles(const glm::vec3 &systemCenter, std::vector<Particle> &particles);

private:
	void emitParticle(const glm::vec3 &center, std::vector<Particle> &particles);
};


#endif //SURVIVE_PARTICLESYSTEM_H
