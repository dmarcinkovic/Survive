//
// Created by david on 14. 10. 2021..
//

#ifndef SURVIVE_CIRCLECOLLIDER2DCOMPONENT_H
#define SURVIVE_CIRCLECOLLIDER2DCOMPONENT_H

#include <Box2D/Box2D.h>

#include "Constants.h"

namespace Survive
{
	struct CircleCollider2DComponent
	{
		b2FixtureDef fixtureDef;
		b2CircleShape circleShape;

		CircleCollider2DComponent() = default;

		CircleCollider2DComponent(float radius, float density, float friction, float elasticity)
		{
			circleShape.m_radius = radius  * Constants::BOX2D_SCALE;
			fixtureDef.density = density;
			fixtureDef.friction = friction;
			fixtureDef.restitution = elasticity;
			fixtureDef.shape = &circleShape;
		}
	};
}

#endif //SURVIVE_CIRCLECOLLIDER2DCOMPONENT_H
