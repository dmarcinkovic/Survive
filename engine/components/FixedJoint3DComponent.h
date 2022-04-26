//
// Created by david on 27.04.22..
//

#ifndef SURVIVE_FIXEDJOINT3DCOMPONENT_H
#define SURVIVE_FIXEDJOINT3DCOMPONENT_H

#include <reactphysics3d/reactphysics3d.h>

#include "JointComponent.h"

namespace Survive
{
	struct FixedJoint3DComponent : public JointComponent
	{
		rp3d::FixedJointInfo jointInfo;

		FixedJoint3DComponent()
				: jointInfo(nullptr, nullptr, rp3d::Vector3{})
		{}
	};
}

#endif //SURVIVE_FIXEDJOINT3DCOMPONENT_H
