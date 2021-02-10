//
// Created by david on 05. 02. 2021..
//

#ifndef SURVIVE_PARTICLE_H
#define SURVIVE_PARTICLE_H


#include "../entity/Entity.h"

class Particle : public Entity
{
	glm::vec3 m_Velocity{};
	glm::vec3 m_Rotation{};

	float m_BlendFactor{};

private:
	float m_GravityEffect{};
	float m_LifeLength{};

	float m_ElapsedTime{};

};


#endif //SURVIVE_PARTICLE_H
