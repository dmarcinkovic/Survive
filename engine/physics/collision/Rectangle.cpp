//
// Created by david on 18. 06. 2020..
//

#include "Rectangle.h"

Rectangle::Rectangle(Entity2D &rectangle, float width, float height, const BodyType &bodyType,
                     const glm::vec2 &initialVelocity)
        : Body(rectangle, bodyType, initialVelocity), m_Height(height), m_Width(width)
{

}
