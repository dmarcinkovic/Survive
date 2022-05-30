//
// Created by david on 21.05.22..
//

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "ParticleRenderer.h"
#include "Components.h"
#include "Constants.h"

void Survive::ParticleRenderer::render(entt::registry &registry, const Camera &camera) const
{
	constexpr int numberOfVaoUnits = 6;
	auto entities = registry.view<ParticleComponent, TagComponent>();

	if (entities.begin() == entities.end())
	{
		return;
	}

	prepareRendering(m_Shader);
	m_Shader.loadProjectionMatrix(camera.getProjectionMatrix());

	for (auto const entity: entities)
	{
		const TagComponent &tag = entities.get<TagComponent>(entity);
		ParticleComponent &particleComponent = entities.get<ParticleComponent>(entity);
		prepareEntity(particleComponent.m_Model, numberOfVaoUnits);

		loadObjectUniforms(registry, entity);
		renderParticle(registry, entity, particleComponent, camera);

		finishRenderingEntity(numberOfVaoUnits);
	}

	finishRendering();
}

std::vector<float> Survive::ParticleRenderer::updateParticles(const std::vector<Particle> &particles,
															  const glm::mat4 &viewMatrix, int index)
{
	std::vector<float> data(particles.size() * Constants::PARTICLE_DATA_LENGTH);
	std::uint64_t dataPointer = 0;
	constexpr glm::vec3 rotation{0.0f};

	for (auto const &particle: particles)
	{
		updateModelViewMatrix(particle.position, rotation, particle.scale, viewMatrix, data, dataPointer);
		updateSpriteIndex(data, dataPointer, index);
	}

	return data;
}

void Survive::ParticleRenderer::updateModelViewMatrix(const glm::vec3 &position, const glm::vec3 &rotation,
													  const glm::vec3 &scale, const glm::mat4 &viewMatrix,
													  std::vector<float> &data, std::uint64_t &dataPointer)
{
	glm::mat4 modelMatrix{1};

	modelMatrix = glm::translate(modelMatrix, position);

	modelMatrix[0][0] = viewMatrix[0][0];
	modelMatrix[0][1] = viewMatrix[1][0];
	modelMatrix[0][2] = viewMatrix[2][0];
	modelMatrix[1][0] = viewMatrix[0][1];
	modelMatrix[1][1] = viewMatrix[1][1];
	modelMatrix[1][2] = viewMatrix[2][1];
	modelMatrix[2][0] = viewMatrix[0][2];
	modelMatrix[2][1] = viewMatrix[1][2];
	modelMatrix[2][2] = viewMatrix[2][2];

	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3{0, 0, 1});
	modelMatrix = glm::scale(modelMatrix, scale);

	glm::mat4 modelViewMatrix = viewMatrix * modelMatrix;
	storeMatrixData(modelViewMatrix, data, dataPointer);
}

void Survive::ParticleRenderer::storeMatrixData(const glm::mat4 &matrix, std::vector<float> &data,
												std::uint64_t &dataPointer)
{
	data[dataPointer++] = matrix[0][0];
	data[dataPointer++] = matrix[0][1];
	data[dataPointer++] = matrix[0][2];
	data[dataPointer++] = matrix[0][3];
	data[dataPointer++] = matrix[1][0];
	data[dataPointer++] = matrix[1][1];
	data[dataPointer++] = matrix[1][2];
	data[dataPointer++] = matrix[1][3];
	data[dataPointer++] = matrix[2][0];
	data[dataPointer++] = matrix[2][1];
	data[dataPointer++] = matrix[2][2];
	data[dataPointer++] = matrix[2][3];
	data[dataPointer++] = matrix[3][0];
	data[dataPointer++] = matrix[3][1];
	data[dataPointer++] = matrix[3][2];
	data[dataPointer++] = matrix[3][3];
}

void Survive::ParticleRenderer::updateSpriteIndex(std::vector<float> &data, std::uint64_t &dataPointer, int index)
{
	data[dataPointer++] = static_cast<float>(index);
}

GLsizeiptr Survive::ParticleRenderer::getVertexCount()
{
	return static_cast<GLsizeiptr>(Constants::MAX_PARTICLE_INSTANCES * Constants::PARTICLE_DATA_LENGTH);
}

void Survive::ParticleRenderer::loadObjectUniforms(const entt::registry &registry, entt::entity entity) const
{
	if (registry.any_of<SpriteSheetComponent>(entity))
	{
		const SpriteSheetComponent &spriteSheet = registry.get<SpriteSheetComponent>(entity);
		m_Shader.loadDimensions(spriteSheet.row, spriteSheet.col);
	} else
	{
		m_Shader.loadDimensions(1, 1);
	}

	if (registry.any_of<SpriteComponent>(entity))
	{
		const SpriteComponent &sprite = registry.get<SpriteComponent>(entity);
		m_Shader.loadColor(sprite.color);
	} else
	{
		m_Shader.loadColor(glm::vec4{0.0f});
	}
}

void Survive::ParticleRenderer::renderParticle(const entt::registry &registry, entt::entity entity,
											   ParticleComponent &particleComponent, const Camera &camera)
{
	std::vector<Particle> &particles = particleComponent.m_Particles;
	int index = getSpriteIndex(registry, entity);
	std::vector<float> data = updateParticles(particles, camera.getViewMatrix(), index);

	auto sizeOfData = static_cast<GLsizeiptr>(particles.size() * Constants::PARTICLE_DATA_LENGTH);
	Loader::updateVBO(particleComponent.m_Vbo, data, sizeOfData);

	auto numberOfParticles = static_cast<GLsizei>(particles.size());
	glDrawElementsInstanced(GL_TRIANGLES, particleComponent.m_Model.vertexCount(), GL_UNSIGNED_INT, nullptr,
							numberOfParticles);
}

int Survive::ParticleRenderer::getSpriteIndex(const entt::registry &registry, entt::entity entity)
{
	if (registry.any_of<SpriteSheetComponent>(entity))
	{
		const SpriteSheetComponent &sprite = registry.get<SpriteSheetComponent>(entity);
		return sprite.currentFrameIndex;
	}

	return 0;
}
