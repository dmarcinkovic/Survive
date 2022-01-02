//
// Created by david on 13. 11. 2021..
//

#ifndef SURVIVE_BOXCOLLIDER3DCOMPONENT_H
#define SURVIVE_BOXCOLLIDER3DCOMPONENT_H

#include <reactphysics3d/reactphysics3d.h>

namespace Survive
{
	struct BoxCollider3DComponent
	{
		rp3d::Vector3 position{};
		rp3d::BoxShape *boxShape{};
		rp3d::Vector3 center{};

		BoxCollider3DComponent() = default;

		explicit BoxCollider3DComponent(const rp3d::Vector3 &position, const rp3d::Vector3 &center = rp3d::Vector3{})
			: position(position), center(center)
		{
		}
	};
}

#endif //SURVIVE_BOXCOLLIDER3DCOMPONENT_H
