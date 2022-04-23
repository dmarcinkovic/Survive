//
// Created by david on 10. 04. 2022..
//

#ifndef SURVIVE_BOXCOLLIDER3DCOMPONENTTEMPLATE_H
#define SURVIVE_BOXCOLLIDER3DCOMPONENTTEMPLATE_H

#include "ComponentTemplate.h"
#include "Collider3DComponentTemplate.h"
#include "EditorUtil.h"
#include "Components.h"

namespace Survive
{
	template<>
	class ComponentTemplate<BoxCollider3DComponent>
	{
	private:
		static constexpr float max = std::numeric_limits<float>::max();

	public:
		static void drawComponent(BoxCollider3DComponent &component, bool *visible)
		{
			ImGui::SetNextItemOpen(true, ImGuiCond_Once);

			if (ImGui::CollapsingHeader("Box collider 3D", visible))
			{
				ImGui::PushID("Box3D");
				ComponentTemplate<Collider3DComponent>::drawComponent(component, nullptr);
				ImGui::PopID();

				ImGui::Columns(2, nullptr, false);

				EditorUtil::drawColumnDragFloat3("Size", "##BoxSize", component.position, 0.01f, 0.0f, max);
				EditorUtil::drawColumnDragFloat3("Center", "##Box3DCenter", component.center);

				ImGui::Columns();
			}
		}
	};
}

#endif //SURVIVE_BOXCOLLIDER3DCOMPONENTTEMPLATE_H
