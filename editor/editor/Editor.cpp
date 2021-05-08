//
// Created by david on 31. 12. 2020..
//


#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include "Editor.h"

Survive::Editor::Editor(GLuint scene)
		: m_Io(ImGui::GetIO()), m_Scene(scene)
{
	m_Io.ConfigFlags = m_Io.ConfigFlags | ImGuiConfigFlags_DockingEnable |
					   ImGuiWindowFlags_UnsavedDocument;

	m_Io.ConfigWindowsMoveFromTitleBarOnly = true;

	setColorStyle();
}

void Survive::Editor::render(entt::registry &registry)
{
	renderPropertyWindow(registry);
	renderSceneWindow();
	renderMenu();
	renderOpenDialog();
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
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

void Survive::Editor::renderOpenDialog()
{
	if (m_OpenDialog)
	{
		m_FileChooser.open(600.0f, 400.0f, &m_OpenDialog);
	}
}

bool &Survive::Editor::isSceneWindowFocused()
{
	return m_IsSceneWindowFocused;
}
