//
// Created by david on 18. 12. 2021..
//

#ifndef SURVIVE_HINGEJOINT2DCOMPONENT_H
#define SURVIVE_HINGEJOINT2DCOMPONENT_H

#include <box2d/box2d.h>
#include <glm/glm.hpp>

#include "entt.hpp"

namespace Survive
{
	struct HingeJoint2DComponent
	{
		b2RevoluteJointDef jointDef{};
		entt::entity connectedBody = entt::null;
		std::string connectedBodyName = "none";

		HingeJoint2DComponent() = default;

		HingeJoint2DComponent(entt::entity connectedBody, const b2Vec2 &anchor, const b2Vec2 &connectedAnchor,
							  bool collideConnected = false, bool useMotor = false, float motorSpeed = 0,
							  float maxTorque = 0, bool useLimits = false, float lowerAngle = 0, float upperAngle = 0)
				: connectedBody(connectedBody)
		{
			jointDef.localAnchorA = anchor;
			jointDef.localAnchorB = connectedAnchor;
			jointDef.collideConnected = collideConnected;
			jointDef.upperAngle = glm::radians(upperAngle);
			jointDef.enableMotor = useMotor;
			jointDef.motorSpeed = motorSpeed;
			jointDef.maxMotorTorque = maxTorque;
			jointDef.enableLimit = useLimits;
			jointDef.lowerAngle = glm::radians(lowerAngle);
		}
	};
}

#endif //SURVIVE_HINGEJOINT2DCOMPONENT_H
