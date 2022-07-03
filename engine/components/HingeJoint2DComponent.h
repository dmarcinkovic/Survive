//
// Created by david on 18. 12. 2021..
//

#ifndef SURVIVE_HINGEJOINT2DCOMPONENT_H
#define SURVIVE_HINGEJOINT2DCOMPONENT_H

#include <box2d/box2d.h>
#include <glm/glm.hpp>
#include <entt.hpp>

#include "JointComponent.h"

namespace Survive
{
	struct HingeJoint2DComponent : public JointComponent
	{
		b2RevoluteJointDef jointDef{};

		HingeJoint2DComponent() = default;

		HingeJoint2DComponent(entt::entity connectedBody, const b2Vec2 &anchor, const b2Vec2 &connectedAnchor,
							  bool collideConnected = false, bool useMotor = false, float motorSpeed = 0,
							  float maxTorque = 0, bool useLimits = false, float lowerAngle = 0, float upperAngle = 0)
				: JointComponent(connectedBody)
		{
			jointDef.localAnchorA = anchor;
			jointDef.localAnchorB = connectedAnchor;
			jointDef.collideConnected = collideConnected;
			jointDef.enableMotor = useMotor;
			jointDef.motorSpeed = motorSpeed;
			jointDef.maxMotorTorque = maxTorque;
			jointDef.enableLimit = useLimits;
			jointDef.lowerAngle = glm::radians(lowerAngle);
			jointDef.upperAngle = glm::radians(upperAngle);
		}
	};
}

#endif //SURVIVE_HINGEJOINT2DCOMPONENT_H
