//
// Created by david on 13. 02. 2021..
//

#include "ParticleSystem.h"
#include "../display/Display.h"
#include "../math/Maths.h"

ParticleSystem::ParticleSystem(const TexturedModel &particleTexture, float particlesPerSecond, float speed,
							   float gravity, float lifeLength, float scale)
		: m_Texture(particleTexture), m_ParticlesPerSecond(particlesPerSecond), m_Speed(speed), m_Gravity(gravity),
		  m_LifeLength(lifeLength), m_AverageScale(scale)
{

}

void ParticleSystem::generateParticles(const glm::vec3 &systemCenter, std::vector<Particle> &particles)
{
	auto deltaTime = static_cast<float>(Display::getFrameTime());
	float particlesToCreate = m_ParticlesPerSecond * deltaTime;

	int count = static_cast<int>(std::round(particlesToCreate));

	for (int i = 0; i < count; ++i)
	{
		emitParticle(systemCenter, particles);
	}
}

void ParticleSystem::emitParticle(const glm::vec3 &center, std::vector<Particle> &particles)
{
	float dirX = Maths::getRandom() * 1.2f - 1.0f;
	float dirZ = Maths::getRandom() * 1.2f - 1.0f;

	glm::vec3 velocity{dirX, 1.0f, dirZ};
	velocity = glm::normalize(velocity) * m_Speed;

	// TODO do not hardcode the number of rows in texture
	particles.emplace_back(Particle(m_Texture, 4, center, velocity, m_Gravity, m_LifeLength));
}

void ParticleSystem::setDirection(const glm::vec3 &direction, float deviation)
{
	m_Direction = direction;
	m_DirectionDeviation = deviation;
}

void ParticleSystem::randomizeRotation()
{
	m_RandomRotation = true;
}

void ParticleSystem::setSpeedError(float speedError)
{
	m_SpeedError = speedError;
}

void ParticleSystem::setLifeError(float lifeError)
{
	m_LifeError = lifeError;
}

float ParticleSystem::generateValue(float average, float errorMargin)
{
	float offset = (Maths::getRandom() - 0.5f) * 2.0f * errorMargin;

	return average + offset;
}

float ParticleSystem::generateRotation() const
{
	if (m_RandomRotation)
	{
		return Maths::getRandom() * 360.0f;
	}

	return 0;
}

glm::vec3 ParticleSystem::generateRandomUnitVectorWithinCone(const glm::vec3 &coneDirection, float angle)
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

glm::vec3 ParticleSystem::generateRandomUnitVector()
{
	float theta = Maths::getRandom() * 2.0f * std::numbers::pi_v<float>;
	float z = Maths::getRandom() * 2.0f - 1;

	return getDirection(z, theta);
}

void ParticleSystem::setScaleError(float scaleError)
{
	m_ScaleError = scaleError;
}

glm::vec4 ParticleSystem::getDirection(float angle)
{
	float cosAngle = std::cos(angle);
	float theta = Maths::getRandom() * 2.0f * std::numbers::pi_v<float>;

	float z = cosAngle + Maths::getRandom() * (1 - cosAngle);
	return glm::vec4{getDirection(z, theta), 1.0f};
}

glm::vec4 ParticleSystem::rotateDirection(const glm::vec3 &coneDirection, const glm::vec4 &direction)
{
	glm::vec3 rotateAxis = glm::cross(coneDirection, glm::vec3{0, 0, 1});
	rotateAxis = glm::normalize(rotateAxis);

	float rotateAngle = std::acos(glm::dot(coneDirection, glm::vec3{0, 0, 1}));

	glm::mat4 rotationMatrix = glm::rotate(glm::mat4{1.0f}, -rotateAngle, rotateAxis);

	return rotationMatrix * direction;
}

glm::vec3 ParticleSystem::getDirection(float z, float theta)
{
	float k = std::sqrt(1 - z * z);
	float x = k * std::cos(theta);
	float y = k * std::sin(theta);

	return glm::vec3{x, y, z};
}
