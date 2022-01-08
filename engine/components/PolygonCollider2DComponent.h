//
// Created by david on 14. 10. 2021..
//

#ifndef SURVIVE_POLYGONCOLLIDER2DCOMPONENT_H
#define SURVIVE_POLYGONCOLLIDER2DCOMPONENT_H

#include <box2d/box2d.h>
#include <vector>

#include "Collider2DComponent.h"

namespace Survive
{
	struct PolygonCollider2DComponent : public Collider2DComponent
	{
		b2PolygonShape polygonShape;

		std::vector<b2Vec2> points;

		PolygonCollider2DComponent() = default;

		PolygonCollider2DComponent(const std::vector<b2Vec2> &points, float density, float friction, float elasticity)
				: Collider2DComponent(density, friction, elasticity), points(points)
		{
			polygonShape.Set(points.data(), static_cast<int>(points.size()));
		}
	};
}

#endif //SURVIVE_POLYGONCOLLIDER2DCOMPONENT_H
