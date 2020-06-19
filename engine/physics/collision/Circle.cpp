//
// Created by david on 18. 06. 2020..
//

#include <iostream>
#include "Circle.h"

Circle::Circle(Entity2D &circle, float radius, const BodyType &bodyType, const glm::vec2 &initialVelocity)
        : Body(circle, bodyType, initialVelocity), m_Radius(radius)
{

}

void Circle::collide(Circle &circle)
{
    std::cout << "Circle - circle " << m_Radius << '\n';
}

void Circle::collide(Rectangle &rectangle)
{
    std::cout << "Circle - rectangle " << m_Radius << '\n';
}

void Circle::collide(Triangle &triangle)
{
    std::cout << "Circle - triangle " << m_Radius << '\n';
}

void Circle::accept(Body &body)
{
    body.collide(*this);
}

