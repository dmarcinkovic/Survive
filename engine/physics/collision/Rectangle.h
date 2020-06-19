//
// Created by david on 18. 06. 2020..
//

#ifndef SURVIVE_RECTANGLE_H
#define SURVIVE_RECTANGLE_H


#include <glm/glm.hpp>
#include <ostream>

#include "../../entity/Entity2D.h"
#include "BodyType.h"
#include "Body.h"

class Circle;

class Triangle;

class Rectangle : public Body
{
private:
    float m_Width, m_Height;

public:
    Rectangle(Entity2D &rectangle, float width, float height, float mass, const BodyType &bodyType,
              const glm::vec2 &initialVelocity = glm::vec2{});

    void collide(Circle &circle) override;

    void collide(Rectangle &rectangle) override;

    void collide(Triangle &triangle) override;

    void accept(Body &body) override;
};


#endif //SURVIVE_RECTANGLE_H
