//
// Created by david on 13. 03. 2022..
//

#ifndef SURVIVE_REFRACTIONCOMPONENTTEMPLATE_H
#define SURVIVE_REFRACTIONCOMPONENTTEMPLATE_H

namespace Survive
{
	template<>
	class ComponentTemplate<RefractionComponent>
	{
	public:
		static void drawComponent(RefractionComponent &component, bool *visible)
		{
			ImGui::SetNextItemOpen(true, ImGuiCond_Once);

			if (ImGui::CollapsingHeader("Refraction", visible))
			{
				ImGui::Columns(2, nullptr, false);
				EditorUtil::drawColumnDragFloat("Refraction index", "##RIndex", component.refractiveIndex, 0, 3, 0.1f);
				EditorUtil::drawColumnDragFloat("Refraction factor", "##RFactor", component.refractiveFactor, 0, 1,
												0.1f);
				ImGui::Columns();
			}
		}
	};
}

#endif //SURVIVE_REFRACTIONCOMPONENTTEMPLATE_H
