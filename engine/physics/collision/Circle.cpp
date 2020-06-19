//
// Created by david on 18. 06. 2020..
//

#include <iostream>
#include "Circle.h"

Circle::Circle(Entity2D &circle, float radius, float mass, const BodyType &bodyType, const glm::vec2 &initialVelocity)
        : Body(circle, bodyType,mass, initialVelocity), m_Radius(radius)
{

}

void Circle::collide(Circle &circle)
{
    if (m_BodyType == BodyType::STATIC)
    {
        std::cout << "error : this should not happen\n";
        return;
    }

    auto position = m_Body.m_Position - circle.m_Body.m_Position;
    float totalDistance = m_Radius + circle.m_Radius;

    if (position.x * position.x + position.y + position.y > totalDistance * totalDistance)
    {
        std::cout << "No collision\n";
        return;
    }

    if (circle.bodyType() == BodyType::DYNAMIC)
    {

    }

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

