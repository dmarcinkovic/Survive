//
// Created by david on 13. 03. 2022..
//

#ifndef SURVIVE_SCRIPTCOMPONENTTEMPLATE_H
#define SURVIVE_SCRIPTCOMPONENTTEMPLATE_H

#include <imgui.h>

#include "Components.h"
#include "ComponentTemplate.h"
#include "ScriptUtil.h"

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
			ImGui::SetNextItemOpen(true, ImGuiCond_Once);

			if (ImGui::CollapsingHeader("Script", visible))
			{
				ImGui::Columns(2);

				loadScript(component.pluginLocation);

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
					std::filesystem::path selectedFile = m_OpenDialog.getSelectedFile();
					std::filesystem::path destination = std::filesystem::temp_directory_path();

					// TODO: change this
					std::filesystem::path libraryLocation(std::filesystem::path("cmake-build-debug") / "lib");
					std::filesystem::path includeDirectory(std::filesystem::path("cmake-build-debug") / "include");

					scriptPath = ScriptUtil::compileScript(selectedFile, destination, libraryLocation,
														   includeDirectory);
				}
			}
		}
	};
}

#endif //SURVIVE_SCRIPTCOMPONENTTEMPLATE_H
