//
// Created by david on 11. 02. 2021..
//

#ifndef SURVIVE_PARTICLERENDERER_H
#define SURVIVE_PARTICLERENDERER_H


#include <unordered_map>

#include "ParticleShader.h"
#include "../camera/Camera.h"
#include "../texture/TexturedModel.h"
#include "Particle.h"
#include "ParticleModel.h"

namespace Survive
{
	class ParticleRenderer
	{
	private:
		constexpr static int MAX_INSTANCES = 10'000;
		constexpr static int INSTANCE_DATA_LENGTH = 21;
		constexpr static int VAO_UNITS = 7;

		static int pointer;
		Loader m_Loader;
		GLuint m_Vbo{};

		std::unordered_map<ParticleModel, std::vector<Particle>, ParticleHash> m_Particles;

		ParticleShader m_Shader;

	public:
		ParticleRenderer();

		void render(const Camera &camera) const;

		std::vector<Particle> &getParticles(const ParticleModel &model);

	private:
		void prepare() const;

		static void finish();

		static void enableBlending();

		static std::vector<float> updateParticles(const std::vector<Particle> &particles, const glm::mat4 &viewMatrix);

		static void updateModelViewMatrix(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale,
										  const glm::mat4 &viewMatrix, std::vector<float> &data);

		static void storeMatrixData(const glm::mat4 &matrix, std::vector<float> &data);

		static void updateTextureCoordinates(const Particle &particle, std::vector<float> &data);

		void addInstanceAttributes(const TexturedModel &model) const;
	};
}


#endif //SURVIVE_PARTICLERENDERER_H
