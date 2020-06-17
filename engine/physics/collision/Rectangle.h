//
// Created by david on 18. 06. 2020..
//

#ifndef SURVIVE_RECTANGLE_H
#define SURVIVE_RECTANGLE_H


#include <glm/glm.hpp>

#include "../../entity/Entity2D.h"
#include "BodyType.h"
#include "Body.h"

class Rectangle : public Body
{
private:
    float m_Width, m_Height;

public:
    Rectangle(Entity2D &rectangle, float width, float height, const BodyType &bodyType, const glm::vec2 &initialVelocity = glm::vec2{});
};


#endif //SURVIVE_RECTANGLE_H
