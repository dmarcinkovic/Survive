//
// Created by david on 08. 01. 2022..
//

#ifndef SURVIVE_COLLIDER2DCOMPONENT_H
#define SURVIVE_COLLIDER2DCOMPONENT_H

#include <box2d/box2d.h>

namespace Survive
{
	struct Collider2DComponent
	{
		b2FixtureDef fixtureDef{};

		Collider2DComponent() = default;

		Collider2DComponent(float density, float friction, float elasticity)
		{
			fixtureDef.density = density;
			fixtureDef.friction = friction;
			fixtureDef.restitution = elasticity;
		}
	};

}

#endif //SURVIVE_COLLIDER2DCOMPONENT_H
