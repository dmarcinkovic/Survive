//
// Created by david on 18. 06. 2020..
//

#include "Triangle.h"

Triangle::Triangle(Entity2D &triangle, float a, float b, float c, const BodyType &bodyType,
                   const glm::vec2 &initialVelocity)
        : Body(triangle, bodyType, initialVelocity), m_A(a), m_B(b), m_C(c)
{

}
