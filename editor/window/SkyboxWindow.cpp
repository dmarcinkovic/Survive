//
// Created by david on 17. 07. 2021..
//

#include <imgui.h>
#include <iostream>

#include "EditorUtil.h"
#include "SkyboxWindow.h"

Survive::SkyboxWindow::SkyboxWindow()
		: m_Textures(N), m_Labels{"Right", "Left", "Top", "Bottom", "Front", "Back"}, m_TextureNames(N)
{
	m_Model = m_Loader.renderCube();
}

void Survive::SkyboxWindow::draw(entt::registry &registry, Renderer &renderer, bool &open)
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
			if (ImGui::Button(m_Labels[i], buttonSize))
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
						m_TextureNames[m_CurrentImage] = filename;
					}
				}
			}
		}

		ImGui::NewLine();
		ImVec2 size(ImGui::GetWindowWidth(), 20);
		if (ImGui::Button("Add skybox", size))
		{
			auto sky = registry.create();
			registry.emplace<Transform3DComponent>(sky, glm::vec3{}, glm::vec3{500.0f});

			registry.emplace<Render3DComponent>(sky, TexturedModel(m_Model, Loader::loadCubeMap(m_TextureNames)));
			renderer.addSkyboxEntity(sky);
		}

		ImGui::EndPopup();
	}

	ImGui::PopStyleColor(2);
}
