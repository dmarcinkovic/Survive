//
// Created by david on 18. 06. 2020..
//

#ifndef SURVIVE_WORLD_H
#define SURVIVE_WORLD_H

#include <variant>
#include <vector>

#include "collision/Circle.h"
#include "collision/Rectangle.h"
#include "collision/Triangle.h"

class World
{
private:
    std::vector<std::variant<Circle, Rectangle, Triangle>> m_Bodies;

public:
    void addBody(Circle &circle);

    void addBody(Rectangle &rectangle);

    void addBody(Triangle &triangle);

    void step();
};


#endif //SURVIVE_WORLD_H
