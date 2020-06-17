//
// Created by david on 18. 06. 2020..
//

#ifndef SURVIVE_CIRCLE_H
#define SURVIVE_CIRCLE_H


#include "../../entity/Entity2D.h"

class Circle
{
private:
    Entity2D &m_Circle;
    float m_Radius;

public:
    explicit Circle(Entity2D &circle, float radius);
};


#endif //SURVIVE_CIRCLE_H
