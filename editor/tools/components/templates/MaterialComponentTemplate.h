//
// Created by david on 13. 03. 2022..
//

#ifndef SURVIVE_MATERIALCOMPONENTTEMPLATE_H
#define SURVIVE_MATERIALCOMPONENTTEMPLATE_H

namespace Survive
{
	template<>
	class ComponentTemplate<MaterialComponent>
	{
	private:
		OpenDialog m_OpenDialog;
		Loader m_Loader;

		bool m_Changed = true;
		bool m_Open = false;

	public:
		void drawComponent(MaterialComponent &component, bool *visible)
		{
			ImGui::SetNextItemOpen(true, ImGuiCond_Once);

			if (ImGui::CollapsingHeader("Material", visible))
			{
				ImGui::Checkbox("Transparent", &component.isTransparent);

				ImGui::Separator();

				ImGui::Checkbox("Use normal mapping", &component.useNormalMapping);

				ImGui::PushID("Material component");
				ImGui::Columns(2);
				EditorUtil::loadTexture(m_OpenDialog, m_Loader, component.normalMap, component.normalMapPath,
										"Normal map: %s", "Load texture", m_Changed, m_Open);

				ImGui::Columns();
				ImGui::PopID();
			}
		}
	};
}

#endif //SURVIVE_MATERIALCOMPONENTTEMPLATE_H
