//
// Created by david on 05. 02. 2021..
//

#include "Particle.h"
#include "../constant/Constants.h"
#include "../display/Display.h"

Particle::Particle(const TexturedModel &particleTexture, int rows, const glm::vec3 &position, const glm::vec3 &velocity,
				   float gravityEffect, float lifeLength, float rotation, float scale)
		: Entity(particleTexture, position, glm::vec3{scale, scale, scale}), m_Rows(rows), m_Velocity(velocity),
		  m_GravityEffect(gravityEffect), m_LifeLength(lifeLength), m_Rotation(rotation)
{

}

bool Particle::update(const Camera &camera)
{


	return false;
}

void Particle::updateTextureCoordInfo()
{
	int stageCount = m_Rows * m_Rows;
	float atlasProgression = getAtlasProgression(stageCount);

	m_BlendFactor = std::fmod(atlasProgression, 1);

	updateTextureOffsets(atlasProgression, stageCount);
}

glm::vec2 Particle::setTextureOffset(int index) const
{
	auto col = static_cast<float>(index % m_Rows);
	auto row = static_cast<float>(std::floor(index / m_Rows));
	auto numberOfRows = static_cast<float>(m_Rows);

	return glm::vec2{col / numberOfRows, row / numberOfRows};
}

float Particle::getAtlasProgression(int stageCount) const
{
	float lifeFactor = m_ElapsedTime / m_LifeLength;
	auto stage = static_cast<float>(stageCount);

	return lifeFactor * stage;
}

void Particle::updateTextureOffsets(float atlasProgression, int stageCount)
{
	int i = std::floor(atlasProgression);
	int j = i < stageCount - 1 ? i + 1 : i;

	m_TextureOffset1 = setTextureOffset(i);
	m_TextureOffset2 = setTextureOffset(j);
}

void Particle::applyGravity()
{
	m_Velocity.y += Constants::GRAVITY * m_GravityEffect * Display::getFrameTime();
}
