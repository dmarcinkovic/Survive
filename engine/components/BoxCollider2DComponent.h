//
// Created by david on 14. 10. 2021..
//

#ifndef SURVIVE_BOXCOLLIDER2DCOMPONENT_H
#define SURVIVE_BOXCOLLIDER2DCOMPONENT_H

#include <box2d/box2d.h>

#include "Collider2DComponent.h"

namespace Survive
{
	struct BoxCollider2DComponent : public Collider2DComponent
	{
		friend class BoxGizmos;

		template<typename ComponentType> friend
		class ComponentTemplate;

		b2PolygonShape boxShape{};

		float width{}, height{};

		b2Vec2 center{0, 0};

	private:
		bool m_Initialized{};

	public:
		BoxCollider2DComponent() = default;

		BoxCollider2DComponent(float width, float height, float density, float friction, float elasticity)
				: Collider2DComponent(density, friction, elasticity), width(width), height(height)
		{
			boxShape.SetAsBox(width, height, center, 0);
			fixtureDef.density = density;
			fixtureDef.friction = friction;
			fixtureDef.restitution = elasticity;
		}
	};
}

#endif //SURVIVE_BOXCOLLIDER2DCOMPONENT_H
