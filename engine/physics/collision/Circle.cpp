//
// Created by david on 18. 06. 2020..
//

#include "Circle.h"

Circle::Circle(Entity2D &circle, float radius, const BodyType &bodyType, const glm::vec2 &initialVelocity)
        : Body(circle, bodyType, initialVelocity), m_Radius(radius)
{

}
