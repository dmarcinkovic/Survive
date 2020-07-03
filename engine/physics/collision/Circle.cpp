//
// Created by david on 18. 06. 2020..
//

#include <iostream>
#include "Circle.h"

Circle::Circle(Entity2D &circle, float radius, float mass, const BodyType &bodyType, const glm::vec2 &initialVelocity)
        : Body(circle, bodyType, mass, initialVelocity), m_Radius(radius)
{

}

void Circle::collide(Circle &circle)
{
    auto position = m_Body.m_Position - circle.m_Body.m_Position;
    float totalDistance = m_Radius + circle.m_Radius;

    if (position.x * position.x + position.y * position.y > totalDistance * totalDistance)
    {
        return;
    }

    if (circle.bodyType() == BodyType::DYNAMIC)
    {
//        std::cout << "Circles are colliding\n";
        float totalMass = circle.m_Mass + m_Mass;
        if (totalDistance == 0)
        {
            return;
        }

        float k1 = m_Mass / totalMass;
        float k2 = circle.m_Mass / totalMass;

        const glm::vec2 velocity = m_Velocity;

        m_Velocity = k1 * velocity + k2 * circle.m_Velocity;
        circle.m_Velocity = k2 * circle.m_Velocity + k1 * velocity;

        glm::vec2 connection = m_Body.m_Position - circle.m_Body.m_Position;
        float len = glm::length(connection);

        glm::vec2 intersectionPoint = (m_Radius / len) * circle.m_Body.m_Position +
                                      (circle.m_Radius / len) * m_Body.m_Position;

        glm::vec2 vec1 = glm::vec2(m_Body.m_Position) - intersectionPoint;
        glm::vec2 vec2 = glm::vec2(circle.m_Body.m_Position) - intersectionPoint;
        vec1 /= 40;
        vec2 /= 10;
        m_Velocity += vec1;
        circle.m_Velocity += vec2;
    } else
    {
        glm::vec2 normal = m_Body.m_Position - circle.m_Body.m_Position;
        m_Velocity = glm::reflect(m_Velocity, glm::normalize(normal));
    }
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

