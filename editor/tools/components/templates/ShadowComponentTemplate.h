//
// Created by david on 13. 03. 2022..
//

#ifndef SURVIVE_SHADOWCOMPONENTTEMPLATE_H
#define SURVIVE_SHADOWCOMPONENTTEMPLATE_H

namespace Survive
{
	template<>
	class ComponentTemplate<ShadowComponent>
	{
	public:
		static void drawComponent(ShadowComponent &component, bool *visible)
		{
			ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0.65f, 0.6f, 0.6f, 1.0f));
			ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.5f, 0.55f, 0.5f, 1.0f));
			ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.4f, 0.4f, 0.4f, 1.0f));

			if (ImGui::CollapsingHeader("Shadow", visible))
			{
				ImGui::Checkbox("Add shadow", &component.loadShadow);
			}

			ImGui::PopStyleColor(3);
		}
	};
}

#endif //SURVIVE_SHADOWCOMPONENTTEMPLATE_H
