//
// Created by david on 18. 06. 2020..
//

#ifndef SURVIVE_WORLD_H
#define SURVIVE_WORLD_H

#include <functional>
#include <vector>

#include "collision/Circle.h"
#include "collision/Rectangle.h"
#include "collision/Triangle.h"

class World
{
private:
    std::vector<std::reference_wrapper<Body>> m_Bodies;

public:
    void addBody(Body &body);

    void step();
};


#endif //SURVIVE_WORLD_H
