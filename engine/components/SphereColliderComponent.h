//
// Created by david on 29. 12. 2021..
//

#ifndef SURVIVE_SPHERECOLLIDERCOMPONENT_H
#define SURVIVE_SPHERECOLLIDERCOMPONENT_H

#include <reactphysics3d/reactphysics3d.h>

namespace Survive
{
	struct SphereColliderComponent
	{
		float radius;
		rp3d::SphereShape *sphereShape{};

		SphereColliderComponent() = default;

		SphereColliderComponent(float radius)
			: radius(radius)
		{
		}
	};
}

#endif //SURVIVE_SPHERECOLLIDERCOMPONENT_H
