//
// Created by david on 22. 05. 2020..
//

#ifndef SURVIVE_TERRAINSHADER_H
#define SURVIVE_TERRAINSHADER_H

#include "../light/Light.h"
#include "../core/shader/Shader.h"

namespace Survive
{
	class TerrainShader : public Shader
	{
	private:
		constexpr static const char *VERTEX_FILE = "engine/shader/sources/TerrainVertexShader.glsl";
		constexpr static const char *FRAGMENT_FILE = "engine/shader/sources/TerrainFragmentShader.glsl";

		GLuint m_LocationTransformationMatrix{};
		GLuint m_LocationProjectionMatrix{};
		GLuint m_LocationViewMatrix{};

		GLuint m_LocationLightProjection{};
		GLuint m_LocationLightView{};

		GLuint m_LocationLightPosition{};
		GLuint m_LocationLightColor{};

		GLuint m_LocationShadowMap{};
		GLuint m_LocationBlendMap{};
		GLuint m_LocationGrass{};
		GLuint m_LocationDirt{};
		GLuint m_LocationRock{};
		GLuint m_LocationFlowers{};

		GLuint m_LocationPlane{};
		GLuint m_LocationAddShadow{};

	public:
		TerrainShader();

		void loadTransformationMatrix(const glm::mat4 &transformationMatrix) const;

		void loadProjectionMatrix(const glm::mat4 &projectionMatrix) const;

		void loadViewMatrix(const glm::mat4 &viewMatrix) const;

		void loadLightProjectionMatrix(const glm::mat4 &projectionMatrix) const;

		void loadLightViewMatrix(const glm::mat4 &viewMatrix) const;

		void loadTextures() const;

		void loadLight(const Light &light) const;

		void loadPlane(const glm::vec4 &plane) const;

		void loadAddShadow(int addShadow) const;

	private:
		void getUniformLocations();
	};
}

#endif //SURVIVE_TERRAINSHADER_H
