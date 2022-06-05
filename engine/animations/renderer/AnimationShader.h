//
// Created by david on 12. 08. 2020..
//

#ifndef SURVIVE_ANIMATIONSHADER_H
#define SURVIVE_ANIMATIONSHADER_H

#include <vector>

#include "JointTransform.h"
#include "ObjectShader.h"

namespace Survive
{
	class AnimationShader : public ObjectShader
	{
	private:
		static inline const char *vertexShaderSource =
#include "AnimationVertexShader.glsl"
		;
		static inline const char *fragmentShaderSource =
#include "AnimationFragmentShader.glsl"
		;
		static constexpr int MAX_JOINTS = 50;

		GLint m_LocationJointTransforms[MAX_JOINTS]{};

	public:
		AnimationShader();

		void loadJointTransforms(const std::vector<glm::mat4> &jointTransforms) const;

	private:
		void loadUniformLocations() override;
	};
}

#endif //SURVIVE_ANIMATIONSHADER_H
