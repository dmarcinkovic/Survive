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

	ImGuiIO &io = ImGui::GetIO();
	auto my_tex_w = (float) io.Fonts->TexWidth;
	auto my_tex_h = (float) io.Fonts->TexHeight;

	auto texture = reinterpret_cast<void*>(Loader::loadTexture("res/rock.png"));

	static int pressed_count = 0;
	for (int i = 0; i < 8; i++)
	{
		ImGui::PushID(i);
		int frame_padding = -1 + i;
		ImVec2 size = ImVec2(32.0f, 32.0f);
		ImVec2 uv0 = ImVec2(0.0f, 0.0f);
		ImVec2 uv1 = ImVec2(32.0f / my_tex_w, 32.0f / my_tex_h);
		ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
		if (ImGui::ImageButton(texture, size, uv0, uv1, frame_padding, bg_col, tint_col))
			pressed_count += 1;
		ImGui::PopID();
		ImGui::SameLine();
	}

	ImGui::End();
}
