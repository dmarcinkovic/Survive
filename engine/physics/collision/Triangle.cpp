//
// Created by david on 18. 06. 2020..
//

#include <iostream>
#include "Triangle.h"

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
