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

		CharacterJoint3DComponent(std::string connectedBodyName, const rp3d::Vector3 &anchor,
								  const rp3d::Vector3 &localAnchor, const rp3d::Vector3 &anchorBody2,
								  bool enableCollision, bool isUsingLocalSpace)
				: JointComponent(std::move(connectedBodyName)), jointInfo(nullptr, nullptr, anchor)
		{
			jointInfo.anchorPointBody1LocalSpace = localAnchor;
			jointInfo.anchorPointBody2LocalSpace = anchorBody2;

			jointInfo.isCollisionEnabled = enableCollision;
			jointInfo.isUsingLocalSpaceAnchors = isUsingLocalSpace;
		}
	};
}

#endif //SURVIVE_CHARACTERJOINT3DCOMPONENT_H
