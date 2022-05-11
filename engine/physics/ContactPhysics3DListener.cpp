//
// Created by david on 08.05.22..
//

#include "ContactPhysics3DListener.h"
#include "Components.h"

Survive::ContactPhysics3DListener::ContactPhysics3DListener(entt::registry &registry)
		: m_Registry(registry)
{

}

void Survive::ContactPhysics3DListener::onContact(const rp3d::CollisionCallback::CallbackData &data)
{
	for (int i = 0; i < data.getNbContactPairs(); ++i)
	{
		ContactPair contact = data.getContactPair(i);

		auto *rigidBody1 = dynamic_cast<rp3d::RigidBody *>(contact.getBody1());
		auto *rigidBody2 = dynamic_cast<rp3d::RigidBody *>(contact.getBody2());

		if (rigidBody1 && rigidBody2)
		{
			void *body1UserData = rigidBody1->getUserData();
			void *body2UserData = rigidBody2->getUserData();
			entt::entity entity1 = *reinterpret_cast<entt::entity*>(&body1UserData);
			entt::entity entity2 = *reinterpret_cast<entt::entity*>(&body2UserData);

			if (contact.getEventType() == rp3d::CollisionCallback::ContactPair::EventType::ContactStart)
			{
				onCollisionEnter(entity1, entity2);
				onCollisionEnter(entity2, entity1);
 			} else if (contact.getEventType() == rp3d::CollisionCallback::ContactPair::EventType::ContactExit)
			{
				onCollisionExit(entity1, entity2);
				onCollisionExit(entity2, entity1);
			}
		}
	}
}

void Survive::ContactPhysics3DListener::onCollisionEnter(entt::entity entity1, entt::entity entity2) const
{
	if (m_Registry.any_of<ScriptComponent>(entity1))
	{
		ScriptComponent &script = m_Registry.get<ScriptComponent>(entity1);

		if (script.script != nullptr)
		{
			script.script->onCollisionEnter(entity2);
		}
	}
}

void Survive::ContactPhysics3DListener::onCollisionExit(entt::entity entity1, entt::entity entity2) const
{
	if (m_Registry.any_of<ScriptComponent>(entity1))
	{
		ScriptComponent &script = m_Registry.get<ScriptComponent>(entity1);

		if (script.script != nullptr)
		{
			script.script->onCollisionExit(entity2);
		}
	}
}
