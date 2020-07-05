//
// Created by david on 18. 06. 2020..
//

#ifndef SURVIVE_BODY_H
#define SURVIVE_BODY_H


#include <glm/glm.hpp>

#include "BodyType.h"
#include "../../entity/Entity2D.h"

class Triangle;

class Circle;

class Rectangle;

class Body
{
protected:
    Entity2D &m_Body;
    glm::vec2 m_Velocity;
    BodyType m_BodyType;

    float m_Mass;

public:
    Body(Entity2D &entity2D, const BodyType &bodyType, float mass, const glm::vec2 &initialVelocity);

    [[nodiscard]] const BodyType &bodyType() const;

    virtual void collide(Circle &circle) = 0;

    virtual void collide(Rectangle &rectangle) = 0;

    virtual void collide(Triangle &triangle) = 0;

    virtual void accept(Body &body) = 0;

    Entity2D &getBody();

    [[nodiscard]] const glm::vec2 &velocity() const;
};

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

class Triangle : public Body
{
private:
    float m_A, m_B, m_C;

public:
    Triangle(Entity2D &triangle, float a, float b, float c, float mass, const BodyType &bodyType,
             const glm::vec2 &initialVelocity = glm::vec2{});

    void collide(Circle &circle) override;

    void collide(Rectangle &rectangle) override;

    void collide(Triangle &triangle) override;

    void accept(Body &body) override;
};

#endif //SURVIVE_BODY_H
