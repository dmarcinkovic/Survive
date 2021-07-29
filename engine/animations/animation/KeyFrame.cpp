//
// Created by david on 01. 10. 2020..
//

#include <utility>

#include "KeyFrame.h"

Survive::KeyFrame::KeyFrame(float timeStamp, std::unordered_map<std::string, JointTransform> jointKeyFrames)
		: m_TimeStamp(timeStamp), m_Pose(std::move(jointKeyFrames))
{
}

float Survive::KeyFrame::timeStamp() const
{
	return m_TimeStamp;
}

const std::unordered_map<std::string, Survive::JointTransform> &Survive::KeyFrame::getPose() const
{
	return m_Pose;
}
