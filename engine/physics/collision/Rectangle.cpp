//
// Created by david on 18. 06. 2020..
//

#include <iostream>
#include "Rectangle.h"

Rectangle::Rectangle(Entity2D &rectangle, float width, float height, const BodyType &bodyType,
                     const glm::vec2 &initialVelocity)
        : Body(rectangle, bodyType, initialVelocity), m_Height(height), m_Width(width)
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
