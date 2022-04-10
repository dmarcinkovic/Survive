//
// Created by david on 10. 04. 2022..
//

#ifndef SURVIVE_SPHERECOLLIDER3DCOMPONENTTEMPLATE_H
#define SURVIVE_SPHERECOLLIDER3DCOMPONENTTEMPLATE_H

#include "Components.h"
#include "Collider3DComponentTemplate.h"
#include "ComponentTemplate.h"
#include "EditorUtil.h"

namespace Survive
{
	template<>
	class ComponentTemplate<SphereCollider3DComponent>
	{
	private:
		static constexpr float max = std::numeric_limits<float>::max();

	public:
		static void drawComponent(SphereCollider3DComponent &component, bool *visible)
		{
			if (ImGui::CollapsingHeader("Sphere collider", visible))
			{
				ImGui::PushID("Sphere3D");
				ComponentTemplate<Collider3DComponent>::drawComponent(component, nullptr);
				ImGui::PopID();

				ImGui::Columns(2, nullptr, false);

				EditorUtil::drawColumnDragFloat("Radius", "##SphereRadius", component.radius, 0, max, 0.1f);
				EditorUtil::drawColumnDragFloat3("Center", "##SphereCenter", component.offset);

				ImGui::Columns();
			}
		}
	};
}

#endif //SURVIVE_SPHERECOLLIDER3DCOMPONENTTEMPLATE_H
