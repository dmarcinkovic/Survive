//
// Created by david on 17. 05. 2020..
//

#ifndef SURVIVE_OBJECTSHADER_H
#define SURVIVE_OBJECTSHADER_H


#include "../core/shader/Shader.h"

namespace Survive
{
	class ObjectShader : public Shader
	{
	private:
		constexpr static const char *VERTEX_SHADER = "engine/core/shader/sources/ObjectVertexShader.glsl";
		constexpr static const char *FRAGMENT_SHADER = "engine/core/shader/sources/ObjectFragmentShader.glsl";

		GLuint m_LocationTransformationMatrix{};
		GLuint m_LocationProjectionMatrix{};
		GLuint m_LocationViewMatrix{};

		GLuint m_LocationLightColor{};
		GLuint m_LocationLightPos{};
		GLuint m_LocationShineDamper{};
		GLuint m_LocationMaterial{};

		GLuint m_LocationCameraPosition{};

		GLuint m_LocationLightViewMatrix{};
		GLuint m_LocationLightProjection{};
		GLuint m_LocationObjectTexture{};
		GLuint m_LocationShadowMap{};

		GLuint m_LocationSkybox{};
		GLuint m_LocationReflectiveFactor{};
		GLuint m_LocationRefractionFactor{};
		GLuint m_LocationRefractionIndex{};

		GLuint m_LocationAddShadow{};

		GLuint m_LocationAddBloom{};
		GLuint m_LocationBloomTexture{};
		GLuint m_LocationBloomStrength{};

		GLuint m_LocationPlane{};

	public:
		ObjectShader();

		void loadTransformationMatrix(const glm::mat4 &transformationMatrix) const;

		void loadProjectionMatrix(const glm::mat4 &projectionMatrix) const;

		void loadViewMatrix(const glm::mat4 &viewMatrix) const;

		void loadLight(const glm::vec3 &lightPos, const glm::vec3 &lightColor, float shineDamper, int material) const;

		void loadCameraPosition(const glm::vec3 &cameraPosition) const;

		void loadLightProjection(const glm::mat4 &lightProjection) const;

		void loadLightViewMatrix(const glm::mat4 &viewMatrix) const;

		void loadTextures() const;

		void loadReflectiveFactor(float reflectiveFactor) const;

		void loadRefractionData(float refractionIndex, float refractionFactor) const;

		void loadAddShadow(bool addShadow) const;

		void loadBloomTexture(float bloomStrength) const;

		void loadBloom(bool loadBloom) const;

		void loadPlane(const glm::vec4 &plane) const;

	private:
		void loadUniformLocations();
	};
}

#endif //SURVIVE_OBJECTSHADER_H
