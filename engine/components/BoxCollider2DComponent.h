//
// Created by david on 14. 10. 2021..
//

#ifndef SURVIVE_BOXCOLLIDER2DCOMPONENT_H
#define SURVIVE_BOXCOLLIDER2DCOMPONENT_H

#include <Box2D/Box2D.h>

namespace Survive
{
	struct BoxCollider2DComponent
	{
		b2FixtureDef fixtureDef{};
		b2PolygonShape boxShape{};

		float width{}, height{};
		float angle{};
		b2Vec2 center{0, 0};

		BoxCollider2DComponent() = default;

		BoxCollider2DComponent(float width, float height, float density, float friction, float elasticity)
			: width(width), height(height)
		{
			boxShape.SetAsBox(width, height, center, angle);
			fixtureDef.density = density;
			fixtureDef.friction = friction;
			fixtureDef.restitution = elasticity;
		}
	};
}

#endif //SURVIVE_BOXCOLLIDER2DCOMPONENT_H
