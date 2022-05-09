//
// Created by david on 27. 02. 2022..
//

#include "ContactPhysics2DListener.h"
#include "Components.h"
#include "entt.hpp"

Survive::ContactPhysics2DListener::ContactPhysics2DListener(entt::registry &registry)
	: m_Registry(registry)
{

}

void Survive::ContactPhysics2DListener::BeginContact(b2Contact *contact)
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

	if (m_Registry.any_of<ScriptComponent>(entityB))
	{
		ScriptComponent &script = m_Registry.get<ScriptComponent>(entityB);

		if (script.script != nullptr)
		{
			script.script->onCollisionEnter(entityA);
		}
	}
}

void Survive::ContactPhysics2DListener::EndContact(b2Contact *contact)
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

	if (m_Registry.any_of<ScriptComponent>(entityB))
	{
		ScriptComponent &script = m_Registry.get<ScriptComponent>(entityB);

		if (script.script != nullptr)
		{
			script.script->onCollisionExit(entityA);
		}
	}
}

std::pair<entt::entity, entt::entity> Survive::ContactPhysics2DListener::getBodies(b2Contact *contact)
{
	auto bodyA = contact->GetFixtureA()->GetUserData().pointer;
	auto entityA = static_cast<entt::entity>(bodyA);

	auto bodyB = contact->GetFixtureB()->GetUserData().pointer;
	auto entityB = static_cast<entt::entity>(bodyB);

	return {entityA, entityB};
}
