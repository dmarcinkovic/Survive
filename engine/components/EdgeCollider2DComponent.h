//
// Created by david on 14. 10. 2021..
//

#ifndef SURVIVE_EDGECOLLIDER2DCOMPONENT_H
#define SURVIVE_EDGECOLLIDER2DCOMPONENT_H

#include <box2d/box2d.h>

#include "Collider2DComponent.h"

namespace Survive
{
	struct EdgeCollider2DComponent : public Collider2DComponent
	{
		friend class EdgeGizmos;

		template<typename ComponentType> friend
		class ComponentTemplate;

		b2EdgeShape edgeShape;

	private:
		bool m_Initialized{};

	public:
		EdgeCollider2DComponent() = default;

		EdgeCollider2DComponent(const b2Vec2 &point1, const b2Vec2 &point2, float density, float friction,
								float elasticity)
				: Collider2DComponent(density, friction, elasticity)
		{
			edgeShape.SetTwoSided(point1, point2);
		}
	};
}

#endif //SURVIVE_EDGECOLLIDER2DCOMPONENT_H
