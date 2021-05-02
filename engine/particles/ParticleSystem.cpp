//
// Created by david on 13. 02. 2021..
//

#include "ParticleSystem.h"
#include "../core/display/Display.h"
#include "../core/math/Maths.h"

Survive::ParticleSystem::ParticleSystem(float particlesPerSecond, float speed, float gravity, float lifeLength,
										float scale)
		: m_ParticlesPerSecond(particlesPerSecond), m_Speed(speed), m_Gravity(gravity), m_LifeLength(lifeLength),
		  m_AverageScale(scale)
{

}

void Survive::ParticleSystem::generateParticles(const glm::vec3 &systemCenter, const ParticleModel &particleModel,
												ParticleRenderer &particleRenderer, const Camera &camera)
{
	std::vector<Particle> &particles = particleRenderer.getParticles(particleModel);

	auto deltaTime = static_cast<float>(Display::getFrameTime());
	float particlesToCreate = m_ParticlesPerSecond * deltaTime;

	int count = static_cast<int>(std::round(particlesToCreate));
	count = updateParticles(particles, camera, count);

	for (int i = 0; i < count && m_EmitParticles; ++i)
	{
		emitParticle(systemCenter, particleModel, particles);
	}
}

void Survive::ParticleSystem::emitParticle(const glm::vec3 &center, const ParticleModel &particleModel,
										   std::vector<Particle> &particles) const
{
	float dirX = Maths::getRandom() * 1.2f - 1.0f;
	float dirZ = Maths::getRandom() * 1.2f - 1.0f;

	glm::vec3 velocity{dirX, 1.0f, dirZ};
	velocity = glm::normalize(velocity) * m_Speed;

	particles.emplace_back(Particle(particleModel, center, velocity, m_Gravity, m_LifeLength));
}

void Survive::ParticleSystem::setDirection(const glm::vec3 &direction, float deviation)
{
	m_Direction = direction;
	m_DirectionDeviation = deviation;
}

void Survive::ParticleSystem::randomizeRotation()
{
	m_RandomRotation = true;
}

void Survive::ParticleSystem::setSpeedError(float speedError)
{
	m_SpeedError = speedError;
}

void Survive::ParticleSystem::setLifeError(float lifeError)
{
	m_LifeError = lifeError;
}

float Survive::ParticleSystem::generateValue(float average, float errorMargin)
{
	float offset = (Maths::getRandom() - 0.5f) * 2.0f * errorMargin;

	return average + offset;
}

float Survive::ParticleSystem::generateRotation() const
{
	if (m_RandomRotation)
	{
		return Maths::getRandom() * 360.0f;
	}

	return 0;
}

glm::vec3 Survive::ParticleSystem::generateRandomUnitVectorWithinCone(const glm::vec3 &coneDirection, float angle)
{
	glm::vec4 direction = getDirection(angle);

	if (coneDirection.x != 0 || coneDirection.y != 0 || (coneDirection.z != 1 && coneDirection.z != -1))
	{
		direction = rotateDirection(coneDirection, direction);
	} else if (coneDirection.z == -1)
	{
		direction.z *= -1;
	}

	return glm::vec3(direction);
}

glm::vec3 Survive::ParticleSystem::generateRandomUnitVector()
{
	float theta = Maths::getRandom() * 2.0f * std::numbers::pi_v<float>;
	float z = Maths::getRandom() * 2.0f - 1;

	return getDirection(z, theta);
}

void Survive::ParticleSystem::setScaleError(float scaleError)
{
	m_ScaleError = scaleError;
}

glm::vec4 Survive::ParticleSystem::getDirection(float angle)
{
	float cosAngle = std::cos(angle);
	float theta = Maths::getRandom() * 2.0f * std::numbers::pi_v<float>;

	float z = cosAngle + Maths::getRandom() * (1 - cosAngle);
	return glm::vec4{getDirection(z, theta), 1.0f};
}

glm::vec4 Survive::ParticleSystem::rotateDirection(const glm::vec3 &coneDirection, const glm::vec4 &direction)
{
	glm::vec3 rotateAxis = glm::cross(coneDirection, glm::vec3{0, 0, 1});
	rotateAxis = glm::normalize(rotateAxis);

	float rotateAngle = std::acos(glm::dot(coneDirection, glm::vec3{0, 0, 1}));

	glm::mat4 rotationMatrix = glm::rotate(glm::mat4{1.0f}, -rotateAngle, rotateAxis);

	return rotationMatrix * direction;
}

glm::vec3 Survive::ParticleSystem::getDirection(float z, float theta)
{
	float k = std::sqrt(1 - z * z);
	float x = k * std::cos(theta);
	float y = k * std::sin(theta);

	return glm::vec3{x, y, z};
}

int Survive::ParticleSystem::updateParticles(std::vector<Particle> &particles, const Camera &camera, int count)
{
	for (Particle &particle : particles)
	{
		if (!particle.update(camera))
		{
			--count;
			particle.reset();
		}
	}

	if (count < 0)
	{
		m_EmitParticles = false;
	}

	return count;
}
