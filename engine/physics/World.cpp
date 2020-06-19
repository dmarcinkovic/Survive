//
// Created by david on 18. 06. 2020..
//

#include <iostream>
#include "World.h"

void World::addBody(std::unique_ptr<Body> body)
{
    m_Bodies.emplace_back(std::move(body));
}

void World::step()
{
    for (int i = 0; i < m_Bodies.size(); ++i)
    {
        for (int j = i + 1; j < m_Bodies.size(); ++j)
        {
            if (m_Bodies[i]->bodyType() == BodyType::STATIC &&
                m_Bodies[j]->bodyType() == BodyType::STATIC)
                continue;

            m_Bodies[i]->accept(*m_Bodies[j].get());
        }
    }
}

