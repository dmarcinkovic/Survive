//
// Created by david on 22.04.22..
//

#ifndef SURVIVE_HINGEJOINT3DCOMPONENT_H
#define SURVIVE_HINGEJOINT3DCOMPONENT_H

#include <reactphysics3d/reactphysics3d.h>

#include "entt.hpp"
#include "JointComponent.h"

namespace Survive
{
	struct HingeJoint3DComponent : public JointComponent
	{
		rp3d::HingeJointInfo jointInfo;

		HingeJoint3DComponent()
				: jointInfo(nullptr, nullptr, rp3d::Vector3{}, rp3d::Vector3{})
		{}
	};
}

#endif //SURVIVE_HINGEJOINT3DCOMPONENT_H
