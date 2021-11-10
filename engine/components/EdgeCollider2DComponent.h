//
// Created by david on 14. 10. 2021..
//

#ifndef SURVIVE_EDGECOLLIDER2DCOMPONENT_H
#define SURVIVE_EDGECOLLIDER2DCOMPONENT_H

#include <Box2D/Box2D.h>

namespace Survive
{
	struct EdgeCollider2DComponent
	{
		friend class EdgeGizmos;

		b2FixtureDef fixtureDef;
		b2EdgeShape edgeShape;

	private:
		bool m_Initialized{};

	public:
		EdgeCollider2DComponent() = default;

		EdgeCollider2DComponent(const b2Vec2 &point1, const b2Vec2 &point2, float density, float friction,
								float elasticity)
		{
			edgeShape.Set(point1, point2);
			fixtureDef.density = density;
			fixtureDef.friction = friction;
			fixtureDef.restitution = elasticity;
		}
	};
}

#endif //SURVIVE_EDGECOLLIDER2DCOMPONENT_H
