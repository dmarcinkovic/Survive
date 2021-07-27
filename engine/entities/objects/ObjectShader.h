//
// Created by david on 17. 05. 2020..
//

#ifndef SURVIVE_OBJECTSHADER_H
#define SURVIVE_OBJECTSHADER_H


#include "Shader.h"

namespace Survive
{
	class ObjectShader : public Shader
	{
	private:
		constexpr static const char *VERTEX_SHADER = "engine/core/shader/sources/ObjectVertexShader.glsl";
		constexpr static const char *FRAGMENT_SHADER = "engine/core/shader/sources/ObjectFragmentShader.glsl";

		GLint m_LocationTransformationMatrix{};
		GLint m_LocationProjectionMatrix{};
		GLint m_LocationViewMatrix{};

		GLint m_LocationLightColor{};
		GLint m_LocationLightPos{};
		GLint m_LocationShineDamper{};
		GLint m_LocationMaterial{};

		GLint m_LocationCameraPosition{};

		GLint m_LocationLightViewMatrix{};
		GLint m_LocationLightProjection{};
		GLint m_LocationObjectTexture{};
		GLint m_LocationShadowMap{};

		GLint m_LocationSkybox{};
		GLint m_LocationReflectiveFactor{};
		GLint m_LocationRefractionFactor{};
		GLint m_LocationRefractionIndex{};

		GLint m_LocationAddShadow{};

		GLint m_LocationAddBloom{};
		GLint m_LocationBloomTexture{};
		GLint m_LocationBloomStrength{};

		GLint m_LocationPlane{};

		GLint m_LocationColor{};
		GLint m_LocationRenderColor{};

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

		void loadColor(const glm::vec4 &color) const;

	private:
		void loadUniformLocations();
	};
}

#endif //SURVIVE_OBJECTSHADER_H
