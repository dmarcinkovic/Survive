//
// Created by david on 24. 01. 2022..
//

#ifndef SURVIVE_HINGEJOINTGIZMOS_H
#define SURVIVE_HINGEJOINTGIZMOS_H

#include "PhysicsGizmosBase.h"
#include "Components.h"

namespace Survive
{
	class HingeJointGizmos : public PhysicsGizmosBase
	{
	public:
		void draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity) override;

		static bool isOver();

		void handleKeyEvents(const EventHandler &eventHandler) override;

	private:
		void drawGizmos(entt::registry &registry, entt::entity bodyA, const Camera &camera);

		void drawAnchorA(entt::registry &registry, entt::entity bodyA, const Camera &camera, const b2Vec2 &anchor);

		void drawAnchorB(entt::registry &registry, entt::entity bodyB, const Camera &camera, const b2Vec2 &anchor);

		ImVec2
		getAnchorPosition(entt::registry &registry, entt::entity body, const Camera &camera, const b2Vec2 &anchor);
	};
}

#endif //SURVIVE_HINGEJOINTGIZMOS_H
