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
		static constexpr const char *VERTEX_SHADER = "engine/core/shader/sources/AnimationVertexShader.glsl";
		static constexpr const char *FRAGMENT_SHADER = "engine/core/shader/sources/AnimationFragmentShader.glsl";
		static constexpr int MAX_JOINTS = 50;

		GLint m_LocationJointTransforms[MAX_JOINTS]{};

	public:
		AnimationShader();

		void loadJointTransforms(const std::vector<glm::mat4> &jointTransforms) const;

	private:
		void loadUniformLocations();
	};
}

#endif //SURVIVE_ANIMATIONSHADER_H
