//
// Created by david on 13. 03. 2022..
//

#ifndef SURVIVE_COLLIDER2DCOMPONENTTEMPLATE_H
#define SURVIVE_COLLIDER2DCOMPONENTTEMPLATE_H

namespace Survive
{
	template<>
	class ComponentTemplate<Collider2DComponent>
	{
	public:
		static void drawComponent(Collider2DComponent &component, bool *)
		{
			b2FixtureDef &fixtureDef = component.fixtureDef;

			EditorUtil::drawColumnInputFloat("Mass", "##Box mass", fixtureDef.density, 0.0f);
			EditorUtil::drawColumnDragFloat("Friction", "##Box friction", fixtureDef.friction, 0, 1, 0.05f);
			EditorUtil::drawColumnInputFloat("Elasticity", "##Box restitution", fixtureDef.restitution, 0.0f, 1.0f);
		}
	};
}

#endif //SURVIVE_COLLIDER2DCOMPONENTTEMPLATE_H
