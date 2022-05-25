//
// Created by david on 21.05.22..
//

#ifndef SURVIVE_PARTICLECOMPONENT_H
#define SURVIVE_PARTICLECOMPONENT_H

#include "TexturedModel.h"
#include "Particle2.h"
#include "Constants.h"

namespace Survive
{
	struct ParticleComponent
	{
	private:
		// TODO: change this when you rename it
		friend class ParticleUpdate;

		friend class ParticleSystem2;

		TexturedModel m_Model{};
		GLuint m_Vbo{};

		std::vector<Particle2> m_Particles;

	public:
		float particlesPerSecond{};
		float speed{};
		float gravity{};
		float lifeLength{};

		ParticleComponent() = default;

		ParticleComponent(const TexturedModel &model, GLuint vbo, float particlesPerSecond,
						  float speed, float gravity, float lifeLength)
				: m_Model(model), m_Vbo(vbo), particlesPerSecond{particlesPerSecond},
				  speed{speed}, gravity{gravity}, lifeLength{lifeLength}
		{
			constexpr int instancedDataLength = Constants::PARTICLE_DATA_LENGTH;

			Loader::addInstancedAttribute(model.vaoID(), vbo, 1, 4, instancedDataLength, 0);
			Loader::addInstancedAttribute(model.vaoID(), vbo, 2, 4, instancedDataLength, 4);
			Loader::addInstancedAttribute(model.vaoID(), vbo, 3, 4, instancedDataLength, 8);
			Loader::addInstancedAttribute(model.vaoID(), vbo, 4, 4, instancedDataLength, 12);
			Loader::addInstancedAttribute(model.vaoID(), vbo, 5, 4, instancedDataLength, 16);
			Loader::addInstancedAttribute(model.vaoID(), vbo, 6, 1, instancedDataLength, 20);
		}
	};
}

#endif //SURVIVE_PARTICLECOMPONENT_H
