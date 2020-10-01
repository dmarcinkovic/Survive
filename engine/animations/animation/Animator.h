//
// Created by david on 01. 10. 2020..
//

#ifndef SURVIVE_ANIMATOR_H
#define SURVIVE_ANIMATOR_H


#include "Animation.h"
#include "AnimatedModel.h"
#include "../joints/Joint.h"

class Animator
{
private:
    Animation m_Animation;
    float animationTime{};

    AnimatedModel m_Model;

public:
    Animator(Animation animation, AnimatedModel animatedModel);

private:
    [[nodiscard]] std::unordered_map<std::string, glm::mat4> calculatePose() const;

    void applyPoseToJoints(const std::unordered_map<std::string, glm::mat4> &currentPose, Joint &joint, const glm::mat4 &parentTransformation);
};


#endif //SURVIVE_ANIMATOR_H
