//
// Created by david on 31. 12. 2020..
//


#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include "Key.h"
#include "Editor.h"

Survive::Editor::Editor(GLuint scene)
		: m_Io(ImGui::GetIO()), m_Scene(scene)
{
	m_Io.ConfigFlags = m_Io.ConfigFlags | ImGuiConfigFlags_DockingEnable |
					   ImGuiWindowFlags_UnsavedDocument;

	m_Io.ConfigWindowsMoveFromTitleBarOnly = true;

	setColorStyle();
}

void Survive::Editor::render(entt::registry &registry, Renderer &renderer)
{
	renderPropertyWindow(registry);
	renderSceneWindow();
	renderMenu();

	renderOpenDialog(registry);
	renderSaveAsDialog(registry);
	renderSaveDialog(registry);
	m_SkyWindow.draw(registry, renderer, m_SkyboxDialog);

	Log::drawLogWindow();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Survive::Editor::newFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Survive::Editor::dock()
{
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
}

void Survive::Editor::renderSceneWindow()
{
	ImGui::Begin("Scene window");

	m_IsSceneWindowFocused = ImGui::IsWindowFocused() && ImGui::IsWindowHovered();

	ImVec2 pos = ImGui::GetCursorScreenPos();

	auto textureId = reinterpret_cast<ImTextureID>(m_Scene);

	m_SceneSize = ImGui::GetWindowSize();

	ImGui::GetWindowDrawList()->AddImage(textureId, pos,
										 ImVec2(pos.x + m_SceneSize.x, pos.y + m_SceneSize.y), ImVec2(0, 1),
										 ImVec2(1, 0));

	ImGui::End();
}

void Survive::Editor::renderPropertyWindow(entt::registry &registry)
{
	if (ImGui::Begin("Scene hierarchy"))
	{
		m_Manager.addEntity(registry);

		ImGui::End();
	}

	if (ImGui::Begin("Property panel"))
	{
		m_Manager.drawPropertyPanel(registry);

		ImGui::End();
	}
}

void Survive::Editor::setColorStyle()
{
	ImGuiStyle *style = &ImGui::GetStyle();
	ImVec4 *colors = style->Colors;

	colors[ImGuiCol_TitleBgActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.0f);

	colors[ImGuiCol_Tab] = ImVec4(0.1f, 0.07f, 0.1f, 1.0f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.13f, 0.1f, 0.13f, 0.8f);
	colors[ImGuiCol_TabActive] = ImVec4(0.306f, 0.32f, 0.329f, 1);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.2f, 0.2f, 0.2f, 0.8f);
}

void Survive::Editor::renderMenu()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("Open", "Ctrl+O", &m_OpenDialog);
			ImGui::MenuItem("Save", "Ctrl+S", &m_SaveDialog);
			ImGui::MenuItem("Save As", "Ctrl+Shift+S", &m_SaveAsDialog);
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Window"))
		{
			ImGui::MenuItem("Skybox", "", &m_SkyboxDialog);
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
}

void Survive::Editor::renderOpenDialog(entt::registry &registry)
{
	if (m_OpenDialog)
	{
		m_OpenWindow.open(600.0f, 400.0f, &m_OpenDialog);

		if (!m_OpenDialog)
		{
			std::string file = m_OpenWindow.getSelectedFile();
			if (!file.empty())
			{
				m_SceneLoader.loadScene(registry, file);
			}
		}
	}
}

bool &Survive::Editor::isSceneWindowFocused()
{
	return m_IsSceneWindowFocused;
}

void Survive::Editor::renderSaveAsDialog(entt::registry &registry)
{
	if (m_SaveAsDialog)
	{
		m_SaveWindow.save(600.0f, 400.0f, &m_SaveAsDialog);

		if (!m_SaveAsDialog)
		{
			std::string selectedFile = m_SaveWindow.getSelectedFile();
			if (!selectedFile.empty())
			{
				m_SavedFile = std::move(selectedFile);
			}

			if (!m_SavedFile.empty())
			{
				// TODO call SceneLoader.save(registry, m_SavedFile);
			}
		}
	}
}

void Survive::Editor::renderSaveDialog(entt::registry &registry)
{
	if (m_SaveDialog)
	{
		if (m_SavedFile.empty())
		{
			m_SaveAsDialog = true;
		} else
		{
			// TODO call SceneLoader.save(registry, m_SavedFile);
		}

		m_SaveDialog = false;
	}
}

void Survive::Editor::handleKeyEvents(const Survive::EventHandler &eventHandler)
{
	if (eventHandler.isKeyControlPressed() && eventHandler.isKeyPressed(Key::O))
	{
		m_OpenDialog = true;
	} else if (eventHandler.isKeyControlPressed() && eventHandler.isKeyPressed(Key::S))
	{
		m_SaveDialog = true;
	} else if (eventHandler.isShiftKeyPressed() && eventHandler.isKeyControlPressed() &&
			   eventHandler.isKeyPressed(Key::S))
	{
		m_SaveAsDialog = true;
	}
}
