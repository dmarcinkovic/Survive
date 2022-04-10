//
// Created by david on 10. 04. 2022..
//

#ifndef SURVIVE_COLLIDER3DCOMPONENTTEMPLATE_H
#define SURVIVE_COLLIDER3DCOMPONENTTEMPLATE_H

#include <imgui.h>

#include "Collider3DComponent.h"
#include "ComponentTemplate.h"
#include "EditorUtil.h"

namespace Survive
{
	template<>
	class ComponentTemplate<Collider3DComponent>
	{
	public:
		static void drawComponent(Collider3DComponent &component, bool *)
		{
			ImGui::TextUnformatted("Material");
			ImGui::Indent();

			ImGui::Columns(2, nullptr, false);

			EditorUtil::drawColumnDragFloat("Bounciness", "##Box3DBounciness", component.bounciness, 0, 1, 0.01f);
			EditorUtil::drawColumnDragFloat("Friction", "##Box3DFriction", component.friction, 0, 1, 0.01f);

			ImGui::Unindent();
			ImGui::Columns();

			ImGui::Separator();
		}
	};
}

#endif //SURVIVE_COLLIDER3DCOMPONENTTEMPLATE_H
