//
// Created by david on 06. 09. 2020..
//

#ifndef SURVIVE_JOINTTRANSFORM_H
#define SURVIVE_JOINTTRANSFORM_H

#include <glm/glm.hpp>
#include "../../core/math/Quaternion.h"

namespace Survive
{
	class JointTransform
	{
	private:
		glm::vec3 m_Position;
		Quaternion m_Rotation;

	public:
		JointTransform(const glm::vec3 &position, const Quaternion &quaternion);

		[[nodiscard]] glm::mat4 getLocalTransform() const;

		static JointTransform
		interpolate(const JointTransform &frameA, const JointTransform &frameB, float progression);

		static glm::vec3 interpolate(const glm::vec3 &start, const glm::vec3 &end, float progression);
	};
}

#endif //SURVIVE_JOINTTRANSFORM_H
