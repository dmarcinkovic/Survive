//
// Created by david on 13. 03. 2022..
//

#ifndef SURVIVE_BOXCOLLIDER2DCOMPONENTTEMPLATE_H
#define SURVIVE_BOXCOLLIDER2DCOMPONENTTEMPLATE_H

#include "ComponentTemplate.h"
#include "Collider2DComponentTemplate.h"
#include "Components.h"

namespace Survive
{
	template<>
	class ComponentTemplate<BoxCollider2DComponent> : public ComponentTemplate<Collider2DComponent>
	{
	public:
		static void drawComponent(BoxCollider2DComponent &component, bool *visible)
		{
			if (ImGui::CollapsingHeader("Box collider 2D", visible))
			{
				ImGui::Columns(2, nullptr, false);

				if (EditorUtil::drawColumnDragFloat("Width", "##Box width", component.width))
				{
					component.boxShape.SetAsBox(component.width, component.height, component.center, 0);
					component.m_Initialized = true;
				}

				if (EditorUtil::drawColumnDragFloat("Height", "##Box height", component.height))
				{
					component.boxShape.SetAsBox(component.width, component.height, component.center, 0);
					component.m_Initialized = true;
				}

				b2Vec2 oldCenter = component.center;
				if (EditorUtil::drawColumnDragFloat2("Center", "##Box center", component.center))
				{
					moveBoxCenter(component.boxShape.m_vertices, component.center - oldCenter);
				}

				ImGui::PushID("Box2D");
				ComponentTemplate<Collider2DComponent>::drawComponent(component, nullptr);
				ImGui::PopID();

				ImGui::Columns();
			}
		}

	private:
		static void moveBoxCenter(b2Vec2 *points, const b2Vec2 &diff)
		{
			points[0] += diff;
			points[1] += diff;
			points[2] += diff;
			points[3] += diff;
		}
	};
}

#endif //SURVIVE_BOXCOLLIDER2DCOMPONENTTEMPLATE_H
