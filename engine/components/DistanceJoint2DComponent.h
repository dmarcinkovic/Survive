//
// Created by david on 22. 01. 2022..
//

#ifndef SURVIVE_DISTANCEJOINT2DCOMPONENT_H
#define SURVIVE_DISTANCEJOINT2DCOMPONENT_H

#include <box2d/box2d.h>
#include <glm/glm.hpp>

#include "entt.hpp"

namespace Survive
{
	struct DistanceJoint2DComponent
	{
		b2DistanceJointDef jointDef{};
		entt::entity connectedBody = entt::null;
		std::string connectedBodyName = "none";

		DistanceJoint2DComponent() = default;

		DistanceJoint2DComponent(entt::entity connectedBody, const b2Vec2 &anchor, const b2Vec2 &connectedAnchor,
								 float minLength, float maxLength, bool collideConnected = false)
				: connectedBody(connectedBody)
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
