//
// Created by david on 14. 10. 2021..
//

#ifndef SURVIVE_POLYGONCOLLIDER2DCOMPONENT_H
#define SURVIVE_POLYGONCOLLIDER2DCOMPONENT_H

#include <box2d/box2d.h>
#include <vector>

namespace Survive
{
	struct PolygonCollider2DComponent
	{
		b2FixtureDef fixtureDef;
		b2PolygonShape polygonShape;

		std::vector<b2Vec2> points;

		PolygonCollider2DComponent() = default;

		PolygonCollider2DComponent(const std::vector<b2Vec2> &points, float density, float friction, float elasticity)
				: points(points)
		{
			polygonShape.Set(points.data(), static_cast<int>(points.size()));
			fixtureDef.density = density;
			fixtureDef.friction = friction;
			fixtureDef.restitution = elasticity;
		}
	};
}

#endif //SURVIVE_POLYGONCOLLIDER2DCOMPONENT_H