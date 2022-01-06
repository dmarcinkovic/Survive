//
// Created by david on 29. 12. 2021..
//

#ifndef SURVIVE_SPHERECOLLIDER3DCOMPONENT_H
#define SURVIVE_SPHERECOLLIDER3DCOMPONENT_H

#include <reactphysics3d/reactphysics3d.h>

namespace Survive
{
	struct SphereCollider3DComponent
	{
		float radius{};

		rp3d::Vector3 offset{0, 0, 0};
		rp3d::SphereShape *sphereShape{};

		SphereCollider3DComponent() = default;

		SphereCollider3DComponent(float radius, const rp3d::Vector3 &offset)
				: radius(radius), offset(offset)
		{
		}
	};
}

#endif //SURVIVE_SPHERECOLLIDER3DCOMPONENT_H
