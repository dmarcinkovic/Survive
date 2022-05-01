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

		FixedJoint3DComponent(std::string connectedBodyName, const rp3d::Vector3 &anchor,
							  const rp3d::Vector3 &localAnchor, const rp3d::Vector3 &anchorBody2,
							  bool isCollisionEnabled, bool isUsingLocalSpace)
				: JointComponent(std::move(connectedBodyName)), jointInfo(nullptr, nullptr, anchor)
		{
			jointInfo.anchorPointBody1LocalSpace = localAnchor;
			jointInfo.anchorPointBody2LocalSpace = anchorBody2;

			jointInfo.isCollisionEnabled = isCollisionEnabled;
			jointInfo.isUsingLocalSpaceAnchors = isUsingLocalSpace;
		}
	};
}

#endif //SURVIVE_FIXEDJOINT3DCOMPONENT_H
