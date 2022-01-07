//
// Created by david on 08. 01. 2022..
//

#ifndef SURVIVE_CAPSULECOLLIDER3DCOMPONENT_H
#define SURVIVE_CAPSULECOLLIDER3DCOMPONENT_H

#include <reactphysics3d/reactphysics3d.h>

#include "Collider3DComponent.h"

namespace Survive
{
	struct CapsuleCollider3DComponent : public Collider3DComponent
	{
		rp3d::CapsuleShape *capsuleShape{};
		rp3d::Vector3 center{};

		float radius{};
		float height{};

		CapsuleCollider3DComponent() = default;

		CapsuleCollider3DComponent(float radius, float height, const rp3d::Vector3 &center = rp3d::Vector3{})
				: radius(radius), height(height), center(center)
		{}
	};
}

#endif //SURVIVE_CAPSULECOLLIDER3DCOMPONENT_H
