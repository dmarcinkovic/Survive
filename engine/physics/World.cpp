//
// Created by david on 18. 06. 2020..
//

#include "World.h"

void World::addBody(Circle &circle)
{
    m_Bodies.emplace_back(circle);
}

void World::addBody(Rectangle &rectangle)
{
    m_Bodies.emplace_back(rectangle);
}

void World::addBody(Triangle &triangle)
{
    m_Bodies.emplace_back(triangle);
}

void World::step()
{
    for (int i = 0; i < m_Bodies.size(); ++i)
    {
        for (int j = i + 1; j < m_Bodies.size(); ++j)
        {

        }
    }
}
