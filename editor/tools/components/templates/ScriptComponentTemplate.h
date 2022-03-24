//
// Created by david on 13. 03. 2022..
//

#ifndef SURVIVE_SCRIPTCOMPONENTTEMPLATE_H
#define SURVIVE_SCRIPTCOMPONENTTEMPLATE_H

#include <imgui.h>

#include "Components.h"
#include "ComponentTemplate.h"

namespace Survive
{
	template<>
	class ComponentTemplate<ScriptComponent>
	{
	public:
		static void drawComponent(ScriptComponent &component, bool *visible)
		{
			if (ImGui::CollapsingHeader("Script", visible))
			{

			}
		}
	};
}

#endif //SURVIVE_SCRIPTCOMPONENTTEMPLATE_H
