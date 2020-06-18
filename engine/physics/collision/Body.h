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
    const BodyType &m_BodyType;

public:
    Body(Entity2D &entity2D, const BodyType &bodyType, const glm::vec2 &initialVelocity);

    [[nodiscard]] const BodyType &bodyType() const;

    virtual void collide(Circle &circle);

    virtual void collide(Rectangle &rectangle);

    virtual void collide(Triangle &triangle);

    virtual void accept(Body &body);
};


#endif //SURVIVE_BODY_H
