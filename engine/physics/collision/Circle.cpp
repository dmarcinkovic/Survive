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
        float totalMass = circle.m_Mass + m_Mass;
        if (totalDistance == 0)
        {
            return;
        }

        float k1 = m_Mass / totalMass;
        float k2 = circle.m_Mass / totalMass;

        m_Velocity = k1 * m_Velocity + k2 * circle.m_Velocity;
        circle.m_Velocity = k2 * circle.m_Velocity + k1 * m_Velocity;
    } else
    {
        glm::vec2 normal = m_Body.m_Position - circle.m_Body.m_Position;
        m_Velocity = glm::reflect(m_Velocity, normal);
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

