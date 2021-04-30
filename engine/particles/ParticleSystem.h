//
// Created by david on 13. 02. 2021..
//

#ifndef SURVIVE_PARTICLESYSTEM_H
#define SURVIVE_PARTICLESYSTEM_H


#include <glm/vec3.hpp>
#include <numbers>

#include "../texture/TexturedModel.h"
#include "Particle.h"
#include "ParticleModel.h"
#include "ParticleRenderer.h"

namespace Survive
{
	class ParticleSystem
	{
	private:
		float m_ParticlesPerSecond, m_Speed, m_Gravity, m_LifeLength, m_AverageScale;
		float m_SpeedError{}, m_LifeError{}, m_ScaleError{};

		bool m_RandomRotation = false;
		bool m_EmitParticles = true;

		glm::vec3 m_Direction{};
		float m_DirectionDeviation{};

	public:
		ParticleSystem(float particlesPerSecond, float speed, float gravity,
					   float lifeLength, float scale);

		void generateParticles(const glm::vec3 &systemCenter, const ParticleModel &particleModel,
							   ParticleRenderer &particleRenderer, const Camera &camera);

		void setDirection(const glm::vec3 &direction, float deviation);

		void randomizeRotation();

		void setSpeedError(float speedError);

		void setLifeError(float lifeError);

		void setScaleError(float scaleError);

	private:
		void emitParticle(const glm::vec3 &center, const ParticleModel &particleModel,
						  std::vector<Particle> &particles) const;

		static float generateValue(float average, float errorMargin);

		[[nodiscard]] float generateRotation() const;

		static glm::vec3 generateRandomUnitVectorWithinCone(const glm::vec3 &coneDirection, float angle);

		static glm::vec3 generateRandomUnitVector();

		static glm::vec4 getDirection(float angle);

		static glm::vec4 rotateDirection(const glm::vec3 &coneDirection, const glm::vec4 &direction);

		static glm::vec3 getDirection(float z, float theta);

		int updateParticles(std::vector<Particle> &particles, const Camera &camera, int count);
	};
}

#endif //SURVIVE_PARTICLESYSTEM_H
