//
// Created by david on 01. 10. 2020..
//

#ifndef SURVIVE_ANIMATEDOBJECT_H
#define SURVIVE_ANIMATEDOBJECT_H

#include <glm/glm.hpp>

#include "../joints/Joint.h"
#include "../../entity/Entity.h"
#include "../../objects/Object3D.h"

class AnimatedObject : public Object3D
{
private:
    Joint m_RootJoint;
    int m_NumberOfJoints;

public:
    AnimatedObject(Joint rootJoint, int numberOfJoints, const TexturedModel &texture, const glm::vec3 &position,
                   const glm::vec3 &rotation = glm::vec3{0, 0, 0}, bool isTransparent = false,
                   float scaleX = 1.0f, float scaleY = 1.0f, float scaleZ = 1.0f);

    Joint &rootJoint();

    [[nodiscard]] std::vector<glm::mat4> getJointTransforms() const;

private:
    void addJointsToArray(const Joint &headJoint, std::vector<glm::mat4> &jointMatrices) const;
};


#endif //SURVIVE_ANIMATEDOBJECT_H
