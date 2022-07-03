//
// Created by david on 08.05.22..
//

#ifndef SURVIVE_CONTACTPHYSICS3DLISTENER_H
#define SURVIVE_CONTACTPHYSICS3DLISTENER_H

#include <reactphysics3d/reactphysics3d.h>
#include <entt.hpp>

namespace Survive
{
	class ContactPhysics3DListener : public rp3d::EventListener
	{
	private:
		entt::registry &m_Registry;

	public:
		explicit ContactPhysics3DListener(entt::registry &registry);

		void onContact(const CallbackData &data) override;

	private:
		void onCollisionEnter(entt::entity entity1, entt::entity entity2) const;
	};
}

#endif //SURVIVE_CONTACTPHYSICS3DLISTENER_H
