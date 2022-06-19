//
// Created by david on 22.04.22..
//

#ifndef SURVIVE_HINGEJOINT3DCOMPONENT_H
#define SURVIVE_HINGEJOINT3DCOMPONENT_H

#include <reactphysics3d/reactphysics3d.h>
#include <entt.hpp>

#include "JointComponent.h"

namespace Survive
{
	struct HingeJoint3DComponent : public JointComponent
	{
		rp3d::HingeJointInfo jointInfo;

		HingeJoint3DComponent()
				: jointInfo(nullptr, nullptr, rp3d::Vector3{}, rp3d::Vector3{})
		{}

		HingeJoint3DComponent(std::string connectedBodyName, const rp3d::Vector3 &anchor, const rp3d::Vector3 &axis,
							  const rp3d::Vector3 &localAnchor, const rp3d::Vector3 &localAxis,
							  const rp3d::Vector3 &anchorBody2, const rp3d::Vector3 &axisBody2,
							  bool useMotor, float motorSpeed, float maxTorque,
							  bool useLimits, float minAngle, float maxAngle,
							  bool enableCollision, bool isUsingLocalSpace)
				: JointComponent(std::move(connectedBodyName)), jointInfo(nullptr, nullptr, anchor, axis)
		{
			jointInfo.anchorPointBody1LocalSpace = localAnchor;
			jointInfo.rotationAxisBody1Local = localAxis;
			jointInfo.anchorPointBody2LocalSpace = anchorBody2;
			jointInfo.rotationAxisBody2Local = axisBody2;

			jointInfo.isMotorEnabled = useMotor;
			jointInfo.motorSpeed = motorSpeed;
			jointInfo.maxMotorTorque = maxTorque;

			jointInfo.isLimitEnabled = useLimits;
			jointInfo.minAngleLimit = minAngle;
			jointInfo.maxAngleLimit = maxAngle;

			jointInfo.isCollisionEnabled = enableCollision;
			jointInfo.isUsingLocalSpaceAnchors = isUsingLocalSpace;
		}
	};
}

#endif //SURVIVE_HINGEJOINT3DCOMPONENT_H
