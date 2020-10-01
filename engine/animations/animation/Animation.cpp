//
// Created by david on 01. 10. 2020..
//

#include "Animation.h"

Animation::Animation(float lengthInSeconds, std::vector<KeyFrame> keyFrames)
    : m_Length(lengthInSeconds), m_KeyFrames(std::move(keyFrames))
{

}

float Animation::getLength() const
{
    return m_Length;
}

const std::vector<KeyFrame> &Animation::keyFrames() const
{
    return m_KeyFrames;
}
