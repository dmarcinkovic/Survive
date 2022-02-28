//
// Created by david on 27. 02. 2022..
//

#include "ContactListener.h"
#include "Components.h"
#include "entt.hpp"

Survive::ContactListener::ContactListener(entt::registry &registry)
	: m_Registry(registry)
{

}

void Survive::ContactListener::BeginContact(b2Contact *contact)
{
	auto[entityA, entityB] = getBodies(contact);

	if (m_Registry.any_of<ScriptComponent>(entityA))
	{
		ScriptComponent &script = m_Registry.get<ScriptComponent>(entityA);

		if (script.script != nullptr)
		{
			script.script->onCollisionEnter(entityB);
		}
	}
}

void Survive::ContactListener::EndContact(b2Contact *contact)
{
	auto[entityA, entityB] = getBodies(contact);

	if (m_Registry.any_of<ScriptComponent>(entityA))
	{
		ScriptComponent &script = m_Registry.get<ScriptComponent>(entityA);

		if (script.script != nullptr)
		{
			script.script->onCollisionExit(entityB);
		}
	}
}

std::pair<entt::entity, entt::entity> Survive::ContactListener::getBodies(b2Contact *contact)
{
	auto bodyA = contact->GetFixtureA()->GetUserData().pointer;
	auto entityA = static_cast<entt::entity>(bodyA);

	auto bodyB = contact->GetFixtureB()->GetUserData().pointer;
	auto entityB = static_cast<entt::entity>(bodyB);

	return {entityA, entityB};
}
