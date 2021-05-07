//
// Created by david on 01. 10. 2020..
//

#ifndef SURVIVE_KEYFRAME_H
#define SURVIVE_KEYFRAME_H

#include <unordered_map>
#include <string>

#include "../joints/JointTransform.h"

namespace Survive
{
	class KeyFrame
	{
	private:
		float m_TimeStamp;
		std::unordered_map<std::string, JointTransform> m_Pose;

	public:
		KeyFrame(float timeStamp, std::unordered_map<std::string, JointTransform> jointKeyFrames);

		float timeStamp() const;

		const std::unordered_map<std::string, JointTransform> &getPose() const;
	};
}

#endif //SURVIVE_KEYFRAME_H
