//
// Created by david on 18. 06. 2020..
//

#ifndef SURVIVE_CIRCLE_H
#define SURVIVE_CIRCLE_H

#include <glm/glm.hpp>
#include <ostream>

#include "../../entity/Entity2D.h"
#include "BodyType.h"
#include "Body.h"

class Triangle;

class Rectangle;

class Circle : public Body
{
private:
    float m_Radius;

public:
    explicit Circle(Entity2D &circle, float radius, float mass, const BodyType &bodyType,
                    const glm::vec2 &initialVelocity = glm::vec2{});

    void collide(Circle &circle) override;

    void collide(Rectangle &rectangle) override;

    void collide(Triangle &triangle) override;

    void accept(Body &body) override;
};


#endif //SURVIVE_CIRCLE_H
