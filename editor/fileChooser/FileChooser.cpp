//
// Created by david on 06. 12. 2020..
//

#include <imgui.h>
#include <filesystem>
#include <iostream>

#include "FileChooser.h"
#include "../../engine/display/Display.h"

void FileChooser::open()
{
	auto[width, height] = Display::getWindowSize<float>();

	ImGui::SetNextWindowSize(ImVec2{width / 2.0f, height / 2.0f}, ImGuiCond_Once);
	ImGui::SetNextWindowPos(ImVec2{width / 4.0f, height / 4.0f}, ImGuiCond_Once);

	bool p_open = true;
	if (ImGui::Begin("Example: Simple layout", &p_open, ImGuiWindowFlags_MenuBar))
	{
		// Left
		static int selected = 0;
		{
			ImGui::BeginChild("left pane", ImVec2(150, 0), true);
			for (int i = 0; i < 100; i++)
			{
				char label[128];
				sprintf(label, "MyObject %d", i);
				if (ImGui::Selectable(label, selected == i))
					selected = i;
			}
			ImGui::EndChild();
		}
		ImGui::SameLine();

		// Right
		{
			ImGui::BeginGroup();
			ImGui::BeginChild("item view",
							  ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
			ImGui::Text("MyObject: %d", selected);
			ImGui::Separator();
			if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
			{
				if (ImGui::BeginTabItem("Description"))
				{
					ImGui::TextWrapped(
							"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. ");
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Details"))
				{
					ImGui::Text("ID: 0123456789");
					ImGui::EndTabItem();
				}
				ImGui::EndTabBar();
			}
			ImGui::EndChild();
			if (ImGui::Button("Revert"))
			{}
			ImGui::SameLine();
			if (ImGui::Button("Save"))
			{}
			ImGui::EndGroup();
		}
	}
	ImGui::End();
}

std::vector<std::string> FileChooser::listDirectory(const std::string &directory)
{
	std::filesystem::directory_iterator directoryIterator(directory);

	std::cout << "Directory: " << directory << '\n';
	for (auto const &file : directoryIterator)
	{
		std::string filename = file.path().filename();
		std::cout << "Filename: " << filename << '\n';

	}
	return std::vector<std::string>();
}

std::vector<std::string> FileChooser::listCurrentDirectory()
{
	return std::vector<std::string>();
}
