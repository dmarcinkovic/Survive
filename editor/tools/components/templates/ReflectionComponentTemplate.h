//
// Created by david on 13. 03. 2022..
//

#ifndef SURVIVE_REFLECTIONCOMPONENTTEMPLATE_H
#define SURVIVE_REFLECTIONCOMPONENTTEMPLATE_H

namespace Survive
{
	template<>
	class ComponentTemplate<ReflectionComponent>
	{
	public:
		static void drawComponent(ReflectionComponent &component, bool *visible)
		{
			ImGui::SetNextItemOpen(true, ImGuiCond_Once);

			if (ImGui::CollapsingHeader("Reflection", visible))
			{
				ImGui::Columns(2, nullptr, false);
				EditorUtil::drawColumnDragFloat("Reflection factor", "##Reflection factor",
												component.reflectionFactor, 0, 1, 0.1f);
				ImGui::Columns();
			}
		}
	};
}

#endif //SURVIVE_REFLECTIONCOMPONENTTEMPLATE_H
