//
// Created by david on 18. 06. 2020..
//

#include "Body.h"

Body::Body(Entity2D &entity2D, const BodyType &bodyType, const glm::vec2 &initialVelocity)
    : m_Body(entity2D), m_BodyType(bodyType), m_Velocity(initialVelocity)
{

}

const BodyType &Body::bodyType() const
{
    return m_BodyType;
}

void Body::collide(Circle &circle)
{

}

void Body::collide(Rectangle &rectangle)
{

}

void Body::collide(Triangle &triangle)
{

}

void Body::accept(Body &body)
{

}
