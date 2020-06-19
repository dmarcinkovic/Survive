//
// Created by david on 18. 06. 2020..
//

#ifndef SURVIVE_WORLD_H
#define SURVIVE_WORLD_H

#include <vector>
#include <memory>

#include "collision/Circle.h"
#include "collision/Rectangle.h"
#include "collision/Triangle.h"

class World
{
private:
    std::vector<std::unique_ptr<Body>> m_Bodies;

public:
    void addBody(std::unique_ptr<Body> body);

    void step();
};


#endif //SURVIVE_WORLD_H
