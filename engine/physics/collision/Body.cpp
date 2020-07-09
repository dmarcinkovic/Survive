//
// Created by david on 18. 06. 2020..
//

#include <iostream>

#include "Body.h"

Body::Body(Entity2D &entity2D, const BodyType &bodyType, float mass, const glm::vec2 &initialVelocity)
        : m_Body(entity2D), m_BodyType(bodyType), m_Mass(mass), m_Velocity(initialVelocity)
{

}

const BodyType &Body::bodyType() const
{
    return m_BodyType;
}

Entity2D &Body::getBody()
{
    return m_Body;
}

const glm::vec2 &Body::velocity() const
{
    return m_Velocity;
}

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

void Circle::collide(Rectangle &r)
{
    BoundingBox box1(r.getBody().m_Position, r.width(), r.height());
    BoundingBox box2(m_Body.m_Position, m_Radius * 2, m_Radius * 2);

    if (!BoundingBox::collide(box1, box2)) return;

    if (r.bodyType() == BodyType::STATIC)
    {
        
        m_Velocity.x *= -1;
    }

    std::cout << "They are colliding\n";
}

void Circle::collide(Triangle &triangle)
{
    std::cout << "Circle - triangle " << m_Radius << '\n';
}

void Circle::accept(Body &body)
{
    body.collide(*this);
}


Rectangle::Rectangle(Entity2D &rectangle, float width, float height, float mass, const BodyType &bodyType,
                     const glm::vec2 &initialVelocity)
        : Body(rectangle, bodyType, mass, initialVelocity), m_Height(height), m_Width(width)
{

}

void Rectangle::collide(Circle &circle)
{
    std::cout << "Rectangle - circle " << m_Width << ' ' << m_Height << '\n';
}

void Rectangle::collide(Rectangle &rectangle)
{
    std::cout << "Rectangle - rectangle " << m_Width << ' ' << m_Height << '\n';
}

void Rectangle::collide(Triangle &triangle)
{
    std::cout << "Rectangle - triangle" << m_Width << ' ' << m_Height << '\n';
}

void Rectangle::accept(Body &body)
{
    body.collide(*this);
}

float Rectangle::width() const
{
    return m_Width;
}

float Rectangle::height() const
{
    return m_Height;
}


Triangle::Triangle(Entity2D &triangle, float a, float b, float c, float mass, const BodyType &bodyType,
                   const glm::vec2 &initialVelocity)
        : Body(triangle, bodyType, mass, initialVelocity), m_A(a), m_B(b), m_C(c)
{

}

void Triangle::collide(Circle &circle)
{
    std::cout << "Triangle - circle " << m_A << ' ' << m_B << ' ' << m_C << '\n';
}

void Triangle::collide(Rectangle &rectangle)
{
    std::cout << "Triangle - rectangle " << m_A << ' ' << m_B << ' ' << m_C << '\n';
}

void Triangle::collide(Triangle &triangle)
{
    std::cout << "Triangle - triangle " << m_A << ' ' << m_B << ' ' << m_C << '\n';
}

void Triangle::accept(Body &body)
{
    body.collide(*this);
}

BoundingBox::BoundingBox(const glm::vec3 &position, float width, float height)
        : m_Position(position), m_Width(width), m_Height(height)
{

}

bool BoundingBox::collide(const BoundingBox &box1, const BoundingBox &box2)
{
    return !(box1.m_Position.x + box1.m_Width / 2 < box2.m_Position.x - box2.m_Width / 2
             || box1.m_Position.y + box1.m_Height / 2 < box2.m_Position.y - box2.m_Height / 2
             || box1.m_Position.x - box1.m_Width / 2 > box2.m_Position.x + box2.m_Width / 2
             || box1.m_Position.y - box1.m_Height / 2 > box2.m_Position.y + box2.m_Height / 2);
}
