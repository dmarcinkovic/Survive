//
// Created by david on 27. 02. 2022..
//

#ifndef SURVIVE_CONTACTLISTENER_H
#define SURVIVE_CONTACTLISTENER_H

#include <box2d/box2d.h>
#include <functional>

#include "entt.hpp"

namespace Survive
{
	class ContactListener : public b2ContactListener
	{
	private:
		entt::registry &m_Registry;

	public:
		explicit ContactListener(entt::registry &registry);

		void BeginContact(b2Contact *contact) override;

		void EndContact(b2Contact *contact) override;

	private:
		static std::pair<entt::entity, entt::entity> getBodies(b2Contact *contact);
	};
}

#endif //SURVIVE_CONTACTLISTENER_H
