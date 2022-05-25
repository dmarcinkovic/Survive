//
// Created by david on 21.05.22..
//

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "ParticleUpdate.h"
#include "Components.h"
#include "Constants.h"

void Survive::ParticleUpdate::render(entt::registry &registry, const Camera &camera) const
{
	constexpr int numberOfVaoUnits = 7;
	auto entities = registry.view<SpriteSheetComponent, ParticleComponent, TagComponent>();
	// TODO consider entities with Render2DComponent and SpriteComponent

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

		m_Shader.loadDimensions(1, 1);

		std::vector<Particle2> &particles = particleComponent.m_Particles;
		std::vector<float> data = updateParticles(particles, camera.getViewMatrix());

		auto sizeOfData = static_cast<GLsizeiptr>(particles.size() * Constants::PARTICLE_DATA_LENGTH);
		Loader::updateVBO(particleComponent.m_Vbo, data, sizeOfData);
		// TODO maybe not needed
//		SpriteSheetComponent &sprite = entities.get<SpriteSheetComponent>(entity);

		auto numberOfParticles = static_cast<GLsizei>(particles.size());
		glDrawElementsInstanced(GL_TRIANGLES, particleComponent.m_Model.vertexCount(), GL_UNSIGNED_INT, nullptr, numberOfParticles);
		finishRenderingEntity(numberOfVaoUnits);
	}

	finishRendering();
}

std::vector<float> Survive::ParticleUpdate::updateParticles(const std::vector<Particle2> &particles,
															const glm::mat4 &viewMatrix)
{
	std::vector<float> data(particles.size() * Constants::PARTICLE_DATA_LENGTH);
	std::uint64_t dataPointer = 0;

	for (auto const &particle: particles)
	{
		updateModelViewMatrix(particle.position, glm::vec3{0.0f}, glm::vec3{0.5f}, viewMatrix, data, dataPointer);
		updateTextureCoordinates(particle, data, dataPointer);
	}

	return data;
}

void Survive::ParticleUpdate::updateModelViewMatrix(const glm::vec3 &position, const glm::vec3 &rotation,
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

void Survive::ParticleUpdate::storeMatrixData(const glm::mat4 &matrix, std::vector<float> &data,
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

void Survive::ParticleUpdate::updateTextureCoordinates(const Particle2 &particle, std::vector<float> &data,
													   std::uint64_t &dataPointer)
{
	data[dataPointer++] = 0.0f;
	data[dataPointer++] = 0.0f;
	data[dataPointer++] = 0.0f;
	data[dataPointer++] = 0.0f;
	data[dataPointer++] = 0.0f;
}

GLsizeiptr Survive::ParticleUpdate::getVertexCount()
{
	return static_cast<GLsizeiptr>(Constants::MAX_PARTICLE_INSTANCES * Constants::PARTICLE_DATA_LENGTH);
}
