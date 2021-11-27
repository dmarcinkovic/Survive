//
// Created by david on 28. 11. 2021..
//

#ifndef SURVIVE_POLYGONGIZMOS_H
#define SURVIVE_POLYGONGIZMOS_H

#include "entt.hpp"
#include "Components.h"
#include "Camera.h"
#include "EventHandler.h"
#include "ColliderGizmos.h"

namespace Survive
{
	class PolygonGizmos : public ColliderGizmos
	{
	public:
		void draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity) override;

		static bool isOver();

	private:
		static void
		initializePolygonCollider(PolygonCollider2DComponent &polygonCollider, const Transform3DComponent &transform);
	};
}


#endif //SURVIVE_POLYGONGIZMOS_H
