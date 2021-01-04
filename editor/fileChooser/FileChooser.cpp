//
// Created by david on 06. 12. 2020..
//

#include <imgui.h>
#include <filesystem>

#include "FileChooser.h"
#include "../../engine/display/Display.h"

void FileChooser::open()
{
	auto[width, height] = Display::getWindowSize<float>();
	static std::vector<std::string> currentDirectory = listCurrentDirectory();

	ImGui::SetNextWindowSize(ImVec2{width / 2.0f, height / 2.0f}, ImGuiCond_Once);
	ImGui::SetNextWindowPos(ImVec2{width / 4.0f, height / 4.0f}, ImGuiCond_Once);

	bool p_open = true;
	if (ImGui::Begin("Example: Simple layout", &p_open, ImGuiWindowFlags_MenuBar))
	{
		// Left
		static int selected = 0;
		{
			static ImGuiTableFlags flags =
					ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_Resizable |
					ImGuiTableFlags_RowBg | ImGuiTableFlags_NoBordersInBody;

			const float TEXT_BASE_WIDTH = ImGui::CalcTextSize("A").x;
			if (ImGui::BeginTable("##3ways", 3, flags))
			{
				ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_NoHide);
				ImGui::TableSetupColumn("Size", ImGuiTableColumnFlags_WidthFixed, TEXT_BASE_WIDTH * 12.0f);
				ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthFixed, TEXT_BASE_WIDTH * 18.0f);
				ImGui::TableHeadersRow();

				for (int i = 0; i < currentDirectory.size(); ++i)
				{
					const std::string &file = currentDirectory[i];
					ImGui::TableNextRow();

					ImGui::TableNextColumn();
					if (ImGui::Selectable(file.c_str(), selected == i))
					{
						selected = i;
					}

					ImGui::TableNextColumn();
					if (ImGui::Selectable("Size", selected == i))
					{
						selected = i;
					}

					ImGui::TableNextColumn();
					if (ImGui::Selectable("Type", selected == i))
					{
						selected = i;
					}
				}

				ImGui::EndTable();
			}
		}
		ImGui::SameLine();
	}
	ImGui::End();
}

std::vector<std::string> FileChooser::listDirectory(const std::string &directory)
{
	std::filesystem::directory_iterator directoryIterator(directory);
	std::vector<std::string> files;

	for (auto const &file : directoryIterator)
	{
		std::string filename = file.path().filename();
		files.emplace_back(filename);
	}

	return files;
}

std::vector<std::string> FileChooser::listCurrentDirectory()
{
	auto workingDirectory = std::filesystem::current_path();

	return listDirectory(std::filesystem::absolute(workingDirectory));
}
