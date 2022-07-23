//
// Created by david on 10. 04. 2022..
//

#ifndef SURVIVE_CAPSULECOLLIDER3DCOMPONENTTEMPLATE_H
#define SURVIVE_CAPSULECOLLIDER3DCOMPONENTTEMPLATE_H

#include "ComponentTemplate.h"
#include "Collider3DComponentTemplate.h"
#include "EditorUtil.h"
#include "Components.h"

namespace Survive
{
	template<>
	class ComponentTemplate<CapsuleCollider3DComponent>
	{
	private:
		static constexpr float maxValue = std::numeric_limits<float>::max();

	public:
		static void drawComponent(CapsuleCollider3DComponent &component, bool *visible)
		{
			ImGui::SetNextItemOpen(true, ImGuiCond_Once);

			if (ImGui::CollapsingHeader("Capsule collider 3D", visible))
			{
				ImGui::PushID("Capsule3D");
				ComponentTemplate<Collider3DComponent>::drawComponent(component, nullptr);
				ImGui::PopID();

				ImGui::Columns(2, nullptr, false);

				EditorUtil::drawColumnDragFloat("Radius", "##CapsuleRadius", component.radius, 0, maxValue, 0.1f);
				EditorUtil::drawColumnDragFloat("Height", "##CapsuleHeight", component.height, 0, maxValue, 0.1f);
				EditorUtil::drawColumnDragFloat3("Center", "##CapsuleCenter", component.center);

				ImGui::Columns();
			}
		}
	};
}

#endif //SURVIVE_CAPSULECOLLIDER3DCOMPONENTTEMPLATE_H
