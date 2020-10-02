//
// Created by david on 01. 10. 2020..
//

#include "AnimatedModel.h"

AnimatedModel::AnimatedModel()
    : m_RootJoint("name", 0, glm::mat4{})
{

}

Joint &AnimatedModel::rootJoint()
{
    return m_RootJoint;
}
