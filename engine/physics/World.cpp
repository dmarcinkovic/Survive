//
// Created by david on 18. 06. 2020..
//

#include "World.h"

void Survive::World::addBody(std::unique_ptr<Body> body)
{
	m_Bodies.emplace_back(std::move(body));
}

void Survive::World::step()
{
	for (int i = 0; i < m_Bodies.size(); ++i)
	{
		for (int j = i + 1; j < m_Bodies.size(); ++j)
		{
			if (m_Bodies[i]->bodyType() == BodyType::STATIC &&
				m_Bodies[j]->bodyType() == BodyType::STATIC)
				continue;

			if (m_Bodies[i]->bodyType() == BodyType::STATIC)
			{
				m_Bodies[i]->accept(*m_Bodies[j].get());
			} else
			{
				m_Bodies[j]->accept(*m_Bodies[i].get());
			}
		}
	}

	for (auto &body : m_Bodies)
	{
		body->getBody().m_Position += glm::vec3(body->velocity(), 0);
	}
}

