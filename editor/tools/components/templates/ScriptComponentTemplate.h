//
// Created by david on 13. 03. 2022..
//

#ifndef SURVIVE_SCRIPTCOMPONENTTEMPLATE_H
#define SURVIVE_SCRIPTCOMPONENTTEMPLATE_H

#include <imgui.h>
#include <sstream>

#include "Components.h"
#include "ComponentTemplate.h"
#include "ScriptUtil.h"
#include "SaveDialog.h"
#include "ScriptEditor.h"

namespace Survive
{
	template<>
	class ComponentTemplate<ScriptComponent>
	{
	private:
		bool m_Open{};
		bool m_SaveDialogOpen{};

		OpenDialog m_OpenDialog{};
		SaveDialog m_SaveDialog{};

	public:
		void drawComponent(ScriptComponent &component, bool *visible)
		{
			ImGui::SetNextItemOpen(true, ImGuiCond_Once);

			if (ImGui::CollapsingHeader("Script", visible))
			{
				ImGui::Columns(2);

				loadScript(component.scriptPath, component.m_PluginLocation);

				ImGui::Columns();

				createNewScript(component);
				drawCompileScriptButton(component);
			}
		}

	private:
		void createNewScript(ScriptComponent &component)
		{
			drawCreateNewScriptButton();

			if (m_SaveDialogOpen)
			{
				m_SaveDialog.open(600.0f, 400.0f, &m_SaveDialogOpen);

				if (!m_SaveDialogOpen && !m_SaveDialog.getSelectedFilename().empty())
				{
					std::filesystem::path path = m_SaveDialog.getSelectedFile();

					createScriptTemplate(path);
					component.scriptPath = absolute(path).string();
				}
			}
		}

		static void createScriptTemplate(const std::filesystem::path &path)
		{
			if (!std::filesystem::exists(path))
			{
				std::ofstream writer(path);
				if (path.has_stem())
				{
					writer << getScriptTemplateText(path.stem().string());
				}
				writer.close();
			}

			ScriptEditor::getInstance().createScript(path);
		}

		void drawCreateNewScriptButton()
		{
			setButtonColorStyle();

			float buttonWidth = 0.55f * ImGui::GetContentRegionAvail().x;
			float buttonHeight = 2.0f * ImGui::GetTextLineHeight();

			float offset = (ImGui::GetContentRegionAvail().x - buttonWidth) / 2.0f;
			ImGui::SetCursorPosX(offset);

			if (ImGui::Button("Create new script", ImVec2(buttonWidth, buttonHeight)))
			{
				m_SaveDialogOpen = true;
			}

			ImGui::PopStyleColor(3);
		}

		static void setButtonColorStyle()
		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.2f, 0.15f, 1.0f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.5f, 0.5f, 0.45f, 1.0f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.3f, 0.25f, 1.0f));
		}

		static std::tuple<std::filesystem::path, std::filesystem::path, std::filesystem::path> getCompileDestination()
		{
			std::filesystem::path destination = std::filesystem::temp_directory_path();
			// TODO: change this
			std::filesystem::path libraryLocation(std::filesystem::path("cmake-build-debug") / "lib");
			std::filesystem::path includeDirectory(std::filesystem::path("cmake-build-debug") / "include");

			return std::make_tuple(destination, libraryLocation, includeDirectory);
		}

		static void drawCompileScriptButton(ScriptComponent &component)
		{
			setButtonColorStyle();

			float buttonWidth = 0.55f * ImGui::GetContentRegionAvail().x;
			float buttonHeight = 2.0f * ImGui::GetTextLineHeight();

			float offset = (ImGui::GetContentRegionAvail().x - buttonWidth) / 2.0f;
			ImGui::SetCursorPosX(offset);

			if (ImGui::Button("Compile script", ImVec2(buttonWidth, buttonHeight)))
			{
				std::filesystem::path scriptPath(component.scriptPath);
				if (!component.scriptPath.empty())
				{
					auto [destination, libraryLocation, includeDirectory] = getCompileDestination();

					std::string pluginLocation = ScriptUtil::compileScript(scriptPath, destination, libraryLocation,
																		   includeDirectory);
				}
			}

			ImGui::PopStyleColor(3);
		}

		void loadScript(std::string &scriptPath, std::string &pluginLocation)
		{
			EditorUtil::showLoadedFile("Script path: %s", scriptPath, "Load script", m_Open);

			if (m_Open)
			{
				m_OpenDialog.open(600.0f, 400.0f, &m_Open);

				if (!m_Open && !m_OpenDialog.getSelectedFilename().empty())
				{
					std::filesystem::path selectedFile = m_OpenDialog.getSelectedFile();
					auto [destination, libraryLocation, includeDirectory] = getCompileDestination();

					pluginLocation = ScriptUtil::compileScript(selectedFile, destination, libraryLocation,
															   includeDirectory);
					if (!pluginLocation.empty())
					{
						scriptPath = absolute(selectedFile).string();
					}
				}
			}
		}

		static std::string getScriptTemplateText(const std::string &scriptName)
		{
			std::stringstream ss;

			ss << R"(#include "ObjectBehaviour.h")" << '\n';
			ss << R"(#include "Components.h")" << "\n\n";
			ss << "namespace Survive\n" << "{\n";
			ss << "\tclass " << scriptName << " : public ObjectBehaviour\n";
			ss << "\t{\n";
			ss << "\tpublic:\n";
			ss << "\t\tvoid update() override\n";
			ss << "\t\t{\n\t\t}\n";
			ss << "\t};\n}\n\n";
			ss << R"(extern "C" Survive::ObjectBehaviour *create())" << '\n';
			ss << "{\n";
			ss << "\treturn new Survive::" << scriptName << "();\n";
			ss << "}\n\n";
			ss << R"(extern "C" void destroy(Survive::ObjectBehaviour *object))" << '\n';
			ss << "{\n";
			ss << "\tdelete object;\n";
			ss << "}\n\n";

			return ss.str();
		}
	};
}

#endif //SURVIVE_SCRIPTCOMPONENTTEMPLATE_H
