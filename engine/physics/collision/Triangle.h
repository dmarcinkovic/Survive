//
// Created by david on 18. 06. 2020..
//

#ifndef SURVIVE_TRIANGLE_H
#define SURVIVE_TRIANGLE_H


#include "../../entity/Entity2D.h"
#include "Body.h"

class Triangle : public Body
{
private:
    float m_A, m_B, m_C;

public:
    Triangle(Entity2D &triangle, float a, float b, float c, const BodyType &bodyType,
             const glm::vec2 &initialVelocity = glm::vec2{});
};


#endif //SURVIVE_TRIANGLE_H
