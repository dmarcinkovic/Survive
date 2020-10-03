//
// Created by david on 01. 10. 2020..
//

#ifndef SURVIVE_ANIMATEDMODEL_H
#define SURVIVE_ANIMATEDMODEL_H

#include <glm/glm.hpp>

#include "../joints/Joint.h"
#include "../../entity/Entity.h"
#include "../../objects/Object3D.h"
#include "Animator.h"

class Animator;

class AnimatedModel : public Object3D
{
private:
    Joint m_RootJoint;
    int m_JointCount;
    Animator m_Animator;

public:
    AnimatedModel(Joint rootJoint, int jointCount, const Animation &animation, const TexturedModel &texture, const glm::vec3 &position,
                  const glm::vec3 &rotation = glm::vec3{0, 0, 0}, bool isTransparent = false,
                  float scaleX = 1.0f, float scaleY = 1.0f, float scaleZ = 1.0f);

    Joint &rootJoint();
};


#endif //SURVIVE_ANIMATEDMODEL_H
