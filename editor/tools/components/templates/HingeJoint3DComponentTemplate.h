//
// Created by david on 22.04.22..
//

#ifndef SURVIVE_HINGEJOINT3DCOMPONENTTEMPLATE_H
#define SURVIVE_HINGEJOINT3DCOMPONENTTEMPLATE_H

#include <imgui.h>

#include "Components.h"
#include "ComponentTemplate.h"

namespace Survive
{
	template<>
	class ComponentTemplate<HingeJoint3DComponent>
	{
	public:
		static void drawComponent(HingeJoint3DComponent &component, bool *visible)
		{
			ImGui::SetNextItemOpen(true, ImGuiCond_Once);

			if (ImGui::CollapsingHeader("Hinge joint 3D", visible))
			{

			}
		}
	};
}

#endif //SURVIVE_HINGEJOINT3DCOMPONENTTEMPLATE_H
