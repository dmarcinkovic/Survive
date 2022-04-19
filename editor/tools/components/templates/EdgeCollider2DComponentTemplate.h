//
// Created by david on 13. 03. 2022..
//

#ifndef SURVIVE_EDGECOLLIDER2DCOMPONENTTEMPLATE_H
#define SURVIVE_EDGECOLLIDER2DCOMPONENTTEMPLATE_H

#include <imgui.h>

#include "ComponentTemplate.h"
#include "Components.h"
#include "Collider2DComponentTemplate.h"

namespace Survive
{
	template<>
	class ComponentTemplate<EdgeCollider2DComponent> : public ComponentTemplate<Collider2DComponent>
	{
	public:
		void drawComponent(EdgeCollider2DComponent &component, bool *visible)
		{
			ImGui::SetNextItemOpen(true, ImGuiCond_Once);

			if (ImGui::CollapsingHeader("Edge collider 2D", visible))
			{
				ImGui::Columns(2, nullptr, false);

				if (EditorUtil::drawColumnDragFloat2("First point", "##Edge p1", component.edgeShape.m_vertex1))
				{
					component.m_Initialized = true;
				}

				if (EditorUtil::drawColumnDragFloat2("Second point", "##Edge p2", component.edgeShape.m_vertex2))
				{
					component.m_Initialized = true;
				}

				ImGui::PushID("Edge2D");
				ComponentTemplate<Collider2DComponent>::drawComponent(component, nullptr);
				ImGui::PopID();

				ImGui::Columns();
			}
		}
	};
}

#endif //SURVIVE_EDGECOLLIDER2DCOMPONENTTEMPLATE_H
