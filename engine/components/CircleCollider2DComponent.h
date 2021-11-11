//
// Created by david on 14. 10. 2021..
//

#ifndef SURVIVE_CIRCLECOLLIDER2DCOMPONENT_H
#define SURVIVE_CIRCLECOLLIDER2DCOMPONENT_H

#include <box2d/box2d.h>

namespace Survive
{
	struct CircleCollider2DComponent
	{
		friend class CircleGizmos;

		b2FixtureDef fixtureDef;
		b2CircleShape circleShape;

	private:
		bool m_Initialized{};

	public:
		CircleCollider2DComponent() = default;

		CircleCollider2DComponent(float radius, float density, float friction, float elasticity)
		{
			circleShape.m_radius = radius;
			fixtureDef.density = density;
			fixtureDef.friction = friction;
			fixtureDef.restitution = elasticity;
		}
	};
}

#endif //SURVIVE_CIRCLECOLLIDER2DCOMPONENT_H
