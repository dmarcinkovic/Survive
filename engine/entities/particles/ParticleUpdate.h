//
// Created by david on 21.05.22..
//

#ifndef SURVIVE_PARTICLEUPDATE_H
#define SURVIVE_PARTICLEUPDATE_H

#include "entt.hpp"
#include "Camera.h"
#include "ParticleShader.h"
#include "Renderer2D.h"
#include "Particle.h"

// TODO rename this to ParticleRenderer when done
namespace Survive
{
	class ParticleUpdate : public Renderer2D
	{
	private:
		ParticleShader m_Shader;

	public:
		void render(entt::registry &registry, const Camera &camera) const;

		static GLsizeiptr getVertexCount();

	private:
		static std::vector<float> updateParticles(const std::vector<Particle> &particles,
												  const glm::mat4 &viewMatrix, int index);

		static void updateModelViewMatrix(const glm::vec3 &position, const glm::vec3 &rotation,
										  const glm::vec3 &scale, const glm::mat4 &viewMatrix,
										  std::vector<float> &data, std::uint64_t &dataPointer);

		static void storeMatrixData(const glm::mat4 &matrix, std::vector<float> &data, std::uint64_t &dataPointer);

		static void updateSpriteIndex(std::vector<float> &data, std::uint64_t &dataPointer, int index);
	};
}

#endif //SURVIVE_PARTICLEUPDATE_H
