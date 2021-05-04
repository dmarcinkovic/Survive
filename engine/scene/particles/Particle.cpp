//
// Created by david on 05. 02. 2021..
//

#include "Particle.h"
#include "Constants.h"
#include "Display.h"

Survive::Particle::Particle(const ParticleModel &particleModel, const glm::vec3 &position, const glm::vec3 &velocity,
							float gravityEffect, float lifeLength, float rotation, float scale)
		: Entity(particleModel.texturedModel, position, glm::vec3{scale, scale, scale}), m_InitialPosition(position),
		  m_InitialVelocity(velocity), m_Rows(particleModel.rows),
		  m_Cols(particleModel.cols), m_Velocity(velocity),
		  m_GravityEffect(gravityEffect), m_LifeLength(lifeLength), m_Rotation(rotation)
{

}

bool Survive::Particle::update(const Camera &camera)
{
	applyGravity();

	glm::vec3 change{m_Velocity};
	change *= Display::getFrameTime();

	m_Position += change;
	m_Distance = glm::length(camera.m_Position - m_Position);

	updateTextureCoordInfo();
	updateTimeElapsed();

	return m_ElapsedTime < m_LifeLength;
}

void Survive::Particle::updateTextureCoordInfo()
{
	unsigned stageCount = m_Rows * m_Cols;
	float atlasProgression = getAtlasProgression(stageCount);

	m_BlendFactor = std::fmod(atlasProgression, 1);

	updateTextureOffsets(atlasProgression, stageCount);
}

glm::vec2 Survive::Particle::setTextureOffset(int index) const
{
	auto col = static_cast<float>(index % m_Cols);
	auto row = static_cast<float>(std::floor(index / m_Cols));
	auto numberOfRows = static_cast<float>(m_Rows);

	return glm::vec2{col / numberOfRows, row / numberOfRows};
}

float Survive::Particle::getAtlasProgression(unsigned stageCount) const
{
	float lifeFactor = m_ElapsedTime / m_LifeLength;
	auto stage = static_cast<float>(stageCount);

	return lifeFactor * stage;
}

void Survive::Particle::updateTextureOffsets(float atlasProgression, unsigned stageCount)
{
	int i = std::floor(atlasProgression);
	int j = i < stageCount - 1 ? i + 1 : i;

	m_TextureOffset1 = setTextureOffset(i);
	m_TextureOffset2 = setTextureOffset(j);
}

void Survive::Particle::applyGravity()
{
	m_Velocity.y += Constants::GRAVITY * m_GravityEffect * Display::getFrameTime();
}

void Survive::Particle::updateTimeElapsed()
{
	m_ElapsedTime += static_cast<float>(Display::getFrameTime());
}

void Survive::Particle::reset()
{
	m_ElapsedTime = m_Distance = 0;

	m_Velocity = m_InitialVelocity;
	m_Position = m_InitialPosition;

	m_TextureOffset1 = m_TextureOffset2 = glm::vec2{};
}
