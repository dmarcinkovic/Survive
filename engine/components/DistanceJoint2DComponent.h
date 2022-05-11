//
// Created by david on 22. 01. 2022..
//

#ifndef SURVIVE_DISTANCEJOINT2DCOMPONENT_H
#define SURVIVE_DISTANCEJOINT2DCOMPONENT_H

#include <box2d/box2d.h>
#include <glm/glm.hpp>

#include "entt.hpp"
#include "JointComponent.h"

namespace Survive
{
	struct DistanceJoint2DComponent : public JointComponent
	{
		b2DistanceJointDef jointDef{};

		DistanceJoint2DComponent() = default;

		DistanceJoint2DComponent(entt::entity connectedBody, const b2Vec2 &anchor, const b2Vec2 &connectedAnchor,
								 float minLength, float maxLength, bool collideConnected = false)
				: JointComponent(connectedBody)
		{
			jointDef.localAnchorA = anchor;
			jointDef.localAnchorB = connectedAnchor;
			jointDef.minLength = minLength;
			jointDef.maxLength = maxLength;
			jointDef.collideConnected = collideConnected;
		}
	};
}

#endif //SURVIVE_DISTANCEJOINT2DCOMPONENT_H
