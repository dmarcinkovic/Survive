//
// Created by david on 06. 12. 2020..
//

#include <imgui.h>

#include "FileChooser.h"
#include "../../engine/display/Display.h"

void FileChooser::open(GLuint texture)
{
	auto[width, height] = Display::getWindowSize<float>();

	ImGui::SetNextWindowSize(ImVec2{width / 2.0f, height / 2.0f}, ImGuiCond_Once);
	ImGui::SetNextWindowPos(ImVec2{width / 4.0f, height / 4.0f}, ImGuiCond_Once);

	ImGui::Begin("Open...");

	for (int i = 0; i < 10; ++i)
	{
		ImGui::PushID(i);
		int frame_padding = -1;
		ImVec2 size = ImVec2(60.0f, 60.0f);
		ImVec2 uv0 = ImVec2(0.0f, 0.0f);
		ImVec2 uv1 = ImVec2(1.0f, 1.0f);
		ImVec4 backgroundColor = ImVec4(0.11f, 0.11f, 0.11f, 1.0f);
		ImVec4 borderColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
		ImGui::ImageButton(reinterpret_cast<void *>(texture), size, uv0, uv1, frame_padding, backgroundColor,
						   borderColor);
		ImGui::PopID();
		ImGui::SameLine();
	}
	ImGui::End();
}
