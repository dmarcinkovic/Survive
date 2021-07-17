//
// Created by david on 17. 07. 2021..
//

#include <imgui.h>

#include "EditorUtil.h"
#include "SkyboxWindow.h"

void Survive::SkyboxWindow::draw(bool &open, const ImVec2 &windowSize)
{
	if (open)
	{
		ImGui::OpenPopup("Skybox");
	}

	ImGui::SetNextWindowSize(windowSize);
	if (ImGui::BeginPopupModal("Skybox", &open, ImGuiWindowFlags_NoDocking))
	{
		EditorUtil::loadTexture(m_FileChooser, m_Left, m_LeftTextureName, "Left texture: %s", "Left side", m_Changed);

		ImGui::End();
	}
}
