//
// Created by david on 13. 03. 2022..
//

#ifndef SURVIVE_CIRCLECOLLIDER2DCOMPONENTTEMPLATE_H
#define SURVIVE_CIRCLECOLLIDER2DCOMPONENTTEMPLATE_H

#include "ComponentTemplate.h"
#include "Collider2DComponentTemplate.h"
#include "Components.h"

namespace Survive
{
	template<>
	class ComponentTemplate<CircleCollider2DComponent> : public ComponentTemplate<Collider2DComponent>
	{
	public:
		void drawComponent(CircleCollider2DComponent &component, bool *visible)
		{
			if (ImGui::CollapsingHeader("Circle collider 2D", visible))
			{
				ImGui::Columns(2, nullptr, false);

				if (EditorUtil::drawColumnDragFloat("Radius", "##Cicle radius", component.circleShape.m_radius))
				{
					component.m_Initialized = true;
				}

				EditorUtil::drawColumnDragFloat2("Center", "##Circle center", component.circleShape.m_p);

				ImGui::PushID("Circle2D");
				ComponentTemplate<Collider2DComponent>::drawComponent(component, nullptr);
				ImGui::PopID();

				ImGui::Columns();
			}
		}
	};
}

#endif //SURVIVE_CIRCLECOLLIDER2DCOMPONENTTEMPLATE_H
