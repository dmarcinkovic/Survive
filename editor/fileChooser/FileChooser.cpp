//
// Created by david on 06. 12. 2020..
//

#include <imgui.h>
#include "FileChooser.h"
#include "../../engine/display/Display.h"

void FileChooser::open()
{
	ImGui::Begin("Open...");

	auto[width, height] = Display::getWindowSize<float>();


//	ImVec2 windowSize{static_cast<float>(width) / 2.0, height / 2};
	ImVec2 windowPosition{};

	ImGui::SetNextWindowSize(ImVec2{400, 400}, ImGuiCond_Once);
	ImGui::SetNextWindowPos(ImVec2{400, 400}, ImGuiCond_Once);

	ImGui::End();
}
