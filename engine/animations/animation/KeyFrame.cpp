//
// Created by david on 01. 10. 2020..
//

#include "KeyFrame.h"

#include <utility>

KeyFrame::KeyFrame(float timeStamp, std::unordered_map<std::string, JointTransform> jointKeyFrames)
    : m_TimeStamp(timeStamp), m_Pose(std::move(jointKeyFrames))
{

}
