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
				ImGui::Columns(2, nullptr, false);
				drawSkyboxEntityDropTarget(component);

				EditorUtil::drawColumnInputBool("Transparent", "##MaterialTransparent", component.isTransparent);

				EditorUtil::drawColumnInputBool("Use normal mapping", "##MaterialNormals", component.useNormalMapping);

				ImGui::PushID("Material component");
				ImGui::Columns(2);
				EditorUtil::loadTexture(m_OpenDialog, m_Loader, component.normalMap, component.normalMapPath,
										"Normal map: %s", "Load texture", m_Changed, m_Open);

				ImGui::Columns();

				ImGui::PopID();
			}
		}

	private:
		static void drawSkyboxEntityDropTarget(MaterialComponent &component)
		{
			std::string &skyboxName = component.skyboxEntityName;
			EditorUtil::drawColumnInputText("##MaterialSkybox", "Sky entity", skyboxName);
			initializeDragDropTarget(component);

			ImGui::NextColumn();
		}

		static void initializeDragDropTarget(MaterialComponent &component)
		{
			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("Entity"))
				{
					auto *data = reinterpret_cast<std::tuple<int, int, const char *> *>(payload->Data);
					if (std::get<0>(*data) == std::get<1>(*data))
					{
						Log::logMessage(LogType::ERROR, "Body A cannot be equal to body B");
					} else
					{
						component.skyboxEntity = static_cast<entt::entity>(std::get<1>(*data));
						component.skyboxEntityName = std::get<2>(*data);
					}
				}

				ImGui::EndDragDropTarget();
			}
		}
	};
}

#endif //SURVIVE_MATERIALCOMPONENTTEMPLATE_H
