//
// Created by david on 26.04.22..
//

#ifndef SURVIVE_CHARACTERJOINT3DCOMPONENT_H
#define SURVIVE_CHARACTERJOINT3DCOMPONENT_H

#include <reactphysics3d/reactphysics3d.h>

#include "JointComponent.h"

namespace Survive
{
	struct CharacterJoint3DComponent : public JointComponent
	{
		rp3d::BallAndSocketJointInfo jointInfo;

		CharacterJoint3DComponent()
				: jointInfo(nullptr, nullptr, rp3d::Vector3{})
		{}
	};
}

#endif //SURVIVE_CHARACTERJOINT3DCOMPONENT_H
