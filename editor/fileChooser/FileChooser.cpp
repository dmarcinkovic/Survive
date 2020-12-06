//
// Created by david on 06. 12. 2020..
//

#include <imgui.h>

#include "FileChooser.h"
#include "../../engine/display/Display.h"
#include "../../engine/renderer/Loader.h"

void FileChooser::open()
{
	auto[width, height] = Display::getWindowSize<float>();

	ImGui::SetNextWindowSize(ImVec2{width / 2.0f, height / 2.0f}, ImGuiCond_Once);
	ImGui::SetNextWindowPos(ImVec2{width / 4.0f, height / 4.0f}, ImGuiCond_Once);

	ImGui::Begin("Open...");

	auto texture = reinterpret_cast<void *>(Loader::loadTexture("res/directory.png"));
	
	ImGui::PushID(0);
	int frame_padding = -1;
	ImVec2 size = ImVec2(60.0f, 60.0f);
	ImVec2 uv0 = ImVec2(0.0f, 0.0f);
	ImVec2 uv1 = ImVec2(1.0f, 1.0f);
	ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	ImGui::ImageButton(texture, size, uv0, uv1, frame_padding, bg_col, tint_col);
	ImGui::PopID();
	ImGui::SameLine();


	ImGui::End();
}
