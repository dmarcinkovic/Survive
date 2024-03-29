//
// Created by david on 21.05.22..
//

#ifndef SURVIVE_PARTICLECOMPONENT_H
#define SURVIVE_PARTICLECOMPONENT_H

#include "TexturedModel.h"
#include "Particle.h"
#include "Constants.h"

namespace Survive
{
	struct ParticleComponent
	{
	private:
		friend class ParticleRenderer;

		friend class ParticleSystem;

		template<typename ComponentType> friend
		class ComponentTemplate;

		TexturedModel m_Model{};
		GLuint m_Vbo{};

		std::vector<Particle> m_Particles;

	public:
		float particlesPerSecond{};
		float speed{};
		float gravity{};
		float lifeLength{};
		float speedError{};

		float lifeError{};
		float scaleError{};
		float directionDeviation{1.0f};

		bool useAdditiveBlending{};
		std::string texturePath;

		ParticleComponent() = default;

		ParticleComponent(const TexturedModel &model, GLuint vbo, float particlesPerSecond, float speed, float gravity,
						  float lifeLength, float speedError = 0.0f, float lifeError = 0.0f, float scaleError = 0.f,
						  float directionDeviation = 1.0f, bool useAdditiveBlending = false)
				: m_Model(model), m_Vbo(vbo), particlesPerSecond(particlesPerSecond), speed(speed), gravity(gravity),
				  lifeLength(lifeLength), speedError(speedError), lifeError(lifeError), scaleError(scaleError),
				  directionDeviation(directionDeviation), useAdditiveBlending(useAdditiveBlending)
		{
			constexpr int instancedDataLength = Constants::PARTICLE_DATA_LENGTH;

			Loader::addInstancedAttribute(model.vaoID(), vbo, 1, 4, instancedDataLength, 0);
			Loader::addInstancedAttribute(model.vaoID(), vbo, 2, 4, instancedDataLength, 4);
			Loader::addInstancedAttribute(model.vaoID(), vbo, 3, 4, instancedDataLength, 8);
			Loader::addInstancedAttribute(model.vaoID(), vbo, 4, 4, instancedDataLength, 12);
			Loader::addInstancedAttribute(model.vaoID(), vbo, 5, 1, instancedDataLength, 16);
		}
	};
}

#endif //SURVIVE_PARTICLECOMPONENT_H
