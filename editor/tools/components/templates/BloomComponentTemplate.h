//
// Created by david on 13. 03. 2022..
//

#ifndef SURVIVE_BLOOMCOMPONENTTEMPLATE_H
#define SURVIVE_BLOOMCOMPONENTTEMPLATE_H

#include "ComponentTemplate.h"
#include "Components.h"
#include "OpenDialog.h"
#include "EditorUtil.h"

namespace Survive
{
	template<>
	class ComponentTemplate<BloomComponent>
	{
	private:
		OpenDialog m_OpenDialog{};
		Loader m_Loader{};

		bool m_Changed = true;
		bool m_Open{};

	public:
		void drawComponent(BloomComponent &component, bool *visible)
		{
			ImGui::SetNextItemOpen(true, ImGuiCond_Once);

			if (ImGui::CollapsingHeader("Bloom", visible))
			{
				ImGui::Columns(2, nullptr, false);
				EditorUtil::drawColumnDragFloat("Bloom strength", "##Bloom strength", component.bloomStrength, 0, 5,
												0.1f);

				ImGui::Separator();

				ImGui::PushID("Bloom component");
				ImGui::Columns(2);
				EditorUtil::loadTexture(m_OpenDialog, m_Loader, component.emissiveTexture, component.textureName,
										"Texture: %s", "Load texture", m_Changed, m_Open);
				ImGui::Columns();
				ImGui::PopID();
			}
		}
	};
}

#endif //SURVIVE_BLOOMCOMPONENTTEMPLATE_H
