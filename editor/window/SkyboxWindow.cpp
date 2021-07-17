//
// Created by david on 17. 07. 2021..
//

#include <imgui.h>
#include <iostream>

#include "EditorUtil.h"
#include "SkyboxWindow.h"

Survive::SkyboxWindow::SkyboxWindow()
		: m_Textures(6), m_TextureNames{"Right", "Left", "Top", "Bottom", "Front", "Back"}
{
}

void Survive::SkyboxWindow::draw(bool &open)
{
	if (open)
	{
		ImGui::OpenPopup("Skybox");
	}

	ImGui::PushStyleColor(ImGuiCol_ModalWindowDimBg, ImVec4(1.0f, 1.0f, 1.0f, 0.1f));
	ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0, 0, 0, 1.0f));

	if (ImGui::BeginPopupModal("Skybox", &open, ImGuiWindowFlags_NoDocking))
	{
		ImGui::Columns(2);
		for (int i = 0; i < m_Textures.size(); ++i)
		{
			auto textureId = reinterpret_cast<ImTextureID>(m_Textures[i].textureId());

			ImVec2 imageSize(100, 100);
			ImGui::Image(textureId, imageSize, ImVec2(0, 1), ImVec2(1, 0));
			
			ImVec2 buttonSize(ImGui::GetColumnWidth() - 10.0f, 0.0f);
			if (ImGui::Button(m_TextureNames[i], buttonSize))
			{
				m_DialogOpen = true;
				m_CurrentImage = i;
			}

			ImGui::NextColumn();
		}

		ImGui::Columns();

		if (m_DialogOpen)
		{
			m_FileChooser.open(600, 400, &m_DialogOpen);

			if (!m_DialogOpen)
			{
				std::string filename = m_FileChooser.getSelectedFile();

				if (!filename.empty())
				{
					Texture image = Loader::loadTexture(filename.c_str());
					if (image.isValidTexture())
					{
						m_Textures[m_CurrentImage] = image;
					}
				}
			}
		}

		ImGui::NewLine();
		ImVec2 size(ImGui::GetWindowWidth(), 20);
		if (ImGui::Button("Add skybox", size))
		{

		}

		ImGui::EndPopup();
	}

	ImGui::PopStyleColor(2);
}
