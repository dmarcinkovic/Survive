//
// Created by david on 14. 10. 2021..
//

#ifndef SURVIVE_POLYGONCOLLIDER2DCOMPONENT_H
#define SURVIVE_POLYGONCOLLIDER2DCOMPONENT_H

#include <Box2D/Box2D.h>
#include <vector>

namespace Survive
{
	struct PolygonCollider2DComponent
	{
		b2FixtureDef fixtureDef;
		b2PolygonShape polygonShape;

		PolygonCollider2DComponent() = default;

		PolygonCollider2DComponent(const std::vector<b2Vec2> &points, float density, float friction, float elasticity)
		{
			polygonShape.Set(points.data(), static_cast<int>(points.size()));
			fixtureDef.density = density;
			fixtureDef.friction = friction;
			fixtureDef.restitution = elasticity;
			fixtureDef.shape = &polygonShape;
		}
	};
}

#endif //SURVIVE_POLYGONCOLLIDER2DCOMPONENT_H
