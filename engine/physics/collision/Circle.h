//
// Created by david on 18. 06. 2020..
//

#ifndef SURVIVE_CIRCLE_H
#define SURVIVE_CIRCLE_H

#include <glm/glm.hpp>

#include "../../entity/Entity2D.h"
#include "BodyType.h"
#include "Body.h"

class Circle : public Body
{
private:
    float m_Radius;

public:
    explicit Circle(Entity2D &circle, float radius, const BodyType &bodyType, const glm::vec2 &initialVelocity = glm::vec2{});

};


#endif //SURVIVE_CIRCLE_H
