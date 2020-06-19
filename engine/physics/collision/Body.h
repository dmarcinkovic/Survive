//
// Created by david on 18. 06. 2020..
//

#ifndef SURVIVE_BODY_H
#define SURVIVE_BODY_H


#include <glm/glm.hpp>

#include "../../entity/Entity2D.h"
#include "BodyType.h"

class Triangle;

class Circle;

class Rectangle;

class Body
{
protected:
    Entity2D &m_Body;
    glm::vec2 m_Velocity;
    BodyType m_BodyType;

public:
    Body(Entity2D &entity2D, const BodyType &bodyType, const glm::vec2 &initialVelocity);

    [[nodiscard]] const BodyType &bodyType() const;

    virtual void collide(Circle &circle) = 0;

    virtual void collide(Rectangle &rectangle) = 0;

    virtual void collide(Triangle &triangle) = 0;

    virtual void accept(Body &body) = 0;
};


#endif //SURVIVE_BODY_H
