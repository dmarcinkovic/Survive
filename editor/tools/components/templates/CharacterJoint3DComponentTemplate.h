//
// Created by david on 26.04.22..
//

#ifndef SURVIVE_CHARACTERJOINT3DCOMPONENTTEMPLATE_H
#define SURVIVE_CHARACTERJOINT3DCOMPONENTTEMPLATE_H

#include "Components.h"
#include "ComponentTemplate.h"
#include "Joint3DComponentTemplate.h"

namespace Survive
{
	template<>
	class ComponentTemplate<CharacterJoint3DComponent> : public Joint3DComponentTemplate
	{
	public:
		static void drawComponent(CharacterJoint3DComponent &component, bool *visible)
		{
			ImGui::SetNextItemOpen(true, ImGuiCond_Once);

			if (ImGui::CollapsingHeader("Character joint 3D", visible))
			{
				ImGui::Columns(2, nullptr, false);

				drawConnectedBodyUI(component);

				ImGui::Columns();
			}
		}
	};
}

#endif //SURVIVE_CHARACTERJOINT3DCOMPONENTTEMPLATE_H
