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
	private:
		bool m_Open{};

		OpenDialog m_OpenDialog{};

	public:
		void drawComponent(ScriptComponent &component, bool *visible)
		{
			if (ImGui::CollapsingHeader("Script", visible))
			{
				ImGui::Columns(2);

				loadScript(component.m_PluginLocation);

				ImGui::Columns();
			}
		}

	private:
		void loadScript(std::string &scriptPath)
		{
			EditorUtil::showLoadedFile("Script path: %s", scriptPath, "Load script", m_Open);

			if (m_Open)
			{
				m_OpenDialog.open(600.0f, 400.0f, &m_Open);

				if (!m_Open && !m_OpenDialog.getSelectedFilename().empty())
				{
					std::filesystem::path file = m_OpenDialog.getSelectedFile();
					std::string selectedFilename = std::filesystem::absolute(file).string();

					scriptPath = selectedFilename;
				}
			}
		}
	};
}

#endif //SURVIVE_SCRIPTCOMPONENTTEMPLATE_H
