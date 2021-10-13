//
// Created by david on 11. 10. 2021..
//

#ifndef SURVIVE_RIGIDBODY2DCOMPONENT_H
#define SURVIVE_RIGIDBODY2DCOMPONENT_H

#include <Box2D/Box2D.h>

namespace Survive
{
	struct RigidBody2DComponent
	{
		b2BodyDef bodyDefinition{};


		RigidBody2DComponent() = default;

		explicit RigidBody2DComponent(b2BodyType bodyType, float linearDrag = 0.0f, b2Vec2 linearVelocity = b2Vec2{},
							 float angularDrag = 0.0f, float gravityScale = 1.0f, bool fixedAngle = false)
		{
			bodyDefinition.type = bodyType;
			bodyDefinition.linearDamping = linearDrag;
			bodyDefinition.linearVelocity = linearVelocity;
			bodyDefinition.angularDamping = angularDrag;
			bodyDefinition.gravityScale = gravityScale;
			bodyDefinition.fixedRotation = fixedAngle;
		}
	};
}

#endif //SURVIVE_RIGIDBODY2DCOMPONENT_H
