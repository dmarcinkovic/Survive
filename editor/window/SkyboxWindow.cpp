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
	setColorStyle();

	if (open)
	{
		ImGui::OpenPopup("Skybox");
	}

	if (ImGui::BeginPopupModal("Skybox", &open, ImGuiWindowFlags_NoDocking))
	{
		drawThumbnails();
		drawOpenDialog();

		ImGui::NewLine();

		drawAddSkyboxButton(registry, renderer, open);

		ImGui::EndPopup();
	}

	resetColorStyle();
}

void Survive::SkyboxWindow::setColorStyle()
{
	ImGui::PushStyleColor(ImGuiCol_ModalWindowDimBg, ImVec4(1.0f, 1.0f, 1.0f, 0.1f));
	ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.38f, 0.38f, 0.38f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.45f, 0.45f, 0.45f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
}

void Survive::SkyboxWindow::resetColorStyle()
{
	ImGui::PopStyleColor(5);
}

void Survive::SkyboxWindow::drawThumbnails()
{
	ImGui::Columns(2);
	for (int i = 0; i < m_Textures.size(); ++i)
	{
		auto textureId = reinterpret_cast<ImTextureID>(m_Textures[i].textureId());

		ImVec2 imageSize(THUMBNAIL_WIDTH, THUMBNAIL_HEIGHT);
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
}

void Survive::SkyboxWindow::drawOpenDialog()
{
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
}

void Survive::SkyboxWindow::drawAddSkyboxButton(entt::registry &registry, Renderer &renderer, bool &open)
{
	ImVec2 size(ImGui::GetWindowWidth(), 0);
	if (ImGui::Button("Add skybox", size))
	{
		if (m_Loaded)
		{
			registry.replace<Render3DComponent>(m_Sky, TexturedModel(m_Model, Loader::loadCubeMap(m_TextureNames)));
		} else
		{
			createSkybox(registry, renderer);
		}

		open = false;
		m_Loaded = true;
	}
}

void Survive::SkyboxWindow::createSkybox(entt::registry &registry, Survive::Renderer &renderer)
{
	m_Sky = registry.create();

	registry.emplace<Transform3DComponent>(m_Sky, glm::vec3{}, glm::vec3{500.0f});
	registry.emplace<Render3DComponent>(m_Sky, TexturedModel(m_Model, Loader::loadCubeMap(m_TextureNames)));
	renderer.addSkyboxEntity(m_Sky);
}
