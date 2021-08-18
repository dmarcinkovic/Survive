//
// Created by david on 12. 08. 2020..
//

#ifndef SURVIVE_ANIMATIONSHADER_H
#define SURVIVE_ANIMATIONSHADER_H

#include <vector>

#include "JointTransform.h"
#include "Shader.h"

namespace Survive
{
	class AnimationShader : public Shader
	{
	private:
		static constexpr const char *VERTEX_SHADER = "engine/core/shader/sources/AnimationVertexShader.glsl";
		static constexpr const char *FRAGMENT_SHADER = "engine/core/shader/sources/AnimationFragmentShader.glsl";
		static constexpr int MAX_JOINTS = 50;

		GLint m_LocationTransformationMatrix{};
		GLint m_LocationViewMatrix{};
		GLint m_LocationProjectionMatrix{};

		GLint m_LocationLightPosition{};
		GLint m_LocationLightColor{};
		GLint m_LocationCameraPosition{};

		GLint m_LocationJointTransforms[MAX_JOINTS]{};
		GLint m_LocationPlane{};

		GLint m_LocationLightProjectionMatrix{};
		GLint m_LocationLightViewMatrix{};

		GLint m_LocationObjectTexture{};
		GLint m_LocationSkybox{};
		GLint m_LocationBloomTexture{};
		GLint m_LocationShadowMap{};

		GLint m_LocationReflectiveFactor{};
		GLint m_LocationRefractionFactor{};
		GLint m_LocationRefractionIndex{};

		GLint m_LocationAddShadow{};
		GLint m_LocationAddBloom{};
		GLint m_LocationBloomStrength{};

		GLint m_LocationColor{};
		GLint m_LocationShineDamper{};
		GLint m_LocationMaterial{};

	public:
		AnimationShader();

		void loadTransformationMatrix(const glm::mat4 &transformationMatrix) const;

		void loadViewMatrix(const glm::mat4 &viewMatrix) const;

		void loadProjectionMatrix(const glm::mat4 &projectionMatrix) const;

		void loadLight(const glm::vec3 &lightPosition, const glm::vec3 &lightColor,
					   float shineDamper, int material) const;

		void loadJointTransforms(const std::vector<glm::mat4> &jointTransforms) const;

		void loadPlane(const glm::vec4 &plane) const;

		void loadColor(const glm::vec4 &color) const;

		void loadBloom(bool loadBloom) const;

		void loadBloomTexture(float bloomStrength) const;

		void loadAddShadow(bool addShadow) const;

		void loadRefractionData(float refractionIndex, float refractionFactor) const;

		void loadReflectionFactor(float reflectionFactor) const;

		void loadTextures() const;

		void loadLightViewMatrix(const glm::mat4 &lightViewMatrix) const;

		void loadLightProjectionMatrix(const glm::mat4 &lightProjectionMatrix) const;

		void loadCameraPosition(const glm::vec3 &cameraPosition) const;

	private:
		void loadUniformLocations();
	};
}

#endif //SURVIVE_ANIMATIONSHADER_H
