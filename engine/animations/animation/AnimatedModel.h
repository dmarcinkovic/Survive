//
// Created by david on 01. 10. 2020..
//

#ifndef SURVIVE_ANIMATEDMODEL_H
#define SURVIVE_ANIMATEDMODEL_H


#include "../joints/Joint.h"

class AnimatedModel
{
private:
    Joint m_RootJoint;

public:
    AnimatedModel();

    Joint &rootJoint();
};


#endif //SURVIVE_ANIMATEDMODEL_H
