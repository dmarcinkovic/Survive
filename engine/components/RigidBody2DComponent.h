//
// Created by david on 11. 10. 2021..
//

#ifndef SURVIVE_RIGIDBODY2DCOMPONENT_H
#define SURVIVE_RIGIDBODY2DCOMPONENT_H

#include <box2d/box2d.h>

namespace Survive
{
	struct RigidBody2DComponent
	{
		b2BodyDef bodyDefinition{};
		b2Body *body{};

		RigidBody2DComponent()
		{
			bodyDefinition.type = b2_staticBody;
		}

		explicit RigidBody2DComponent(b2BodyType bodyType, float linearDrag = 0.0f,
									  b2Vec2 linearVelocity = b2Vec2{0, 0},
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
