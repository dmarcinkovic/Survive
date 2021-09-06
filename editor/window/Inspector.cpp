//
// Created by david on 05. 09. 2021..
//

#include "Inspector.h"

Survive::Inspector::Inspector()
{
	// TODO load bolded text
}

void Survive::Inspector::draw(bool &open)
{
	ImGui::Begin("Inspector");

	if (open)
	{
		ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.2f, 0.2f, 0.2f, 1));

		char buffer[] = "Text";
		ImGui::InputText("##Text", buffer, sizeof(buffer), ImGuiInputTextFlags_ReadOnly);
		ImGui::Separator();

		ImGui::Text("Position");
		ImGui::Separator();

		ImGui::Text("Character");
		ImGui::Separator();
		ImGui::Indent();
		ImGui::Text("Font");
		ImGui::Text("Font size");

		ImGui::Unindent();

		ImGui::Text("Color");

		ImGui::PopStyleColor();
	}

	ImGui::End();
}
