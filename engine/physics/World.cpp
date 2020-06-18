//
// Created by david on 18. 06. 2020..
//

#include "World.h"

void World::addBody(Body &body)
{
    m_Bodies.emplace_back(body);
}

void World::step()
{
    for (int i = 0; i < m_Bodies.size(); ++i)
    {
        auto &body = m_Bodies[i].get();

        if (body.bodyType() == BodyType::STATIC) continue;

        for (int j = i + 1; j < m_Bodies.size(); ++j)
        {
            body.accept(m_Bodies[j].get());
        }
    }
}

