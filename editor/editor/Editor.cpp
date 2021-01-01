//
// Created by david on 31. 12. 2020..
//

#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include "Editor.h"

Editor::Editor(GLuint scene)
		: m_Io(ImGui::GetIO()), m_Scene(scene), m_ClearColor(0.45f, 0.55f, 0.60f, 1.00f)
{
	m_Io.ConfigFlags = static_cast<unsigned>(m_Io.ConfigFlags) | ImGuiConfigFlags_DockingEnable |
					   ImGuiWindowFlags_UnsavedDocument;

	setColorStyle();
}

void Editor::render()
{
	renderPropertyWindow();
	renderSceneWindow();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Editor::newFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Editor::dock()
{
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
}

void Editor::renderSceneWindow()
{
	ImGui::Begin("Scene window");
	ImVec2 pos = ImGui::GetCursorScreenPos();
	auto textureId = reinterpret_cast<ImTextureID>(m_Scene);

	m_SceneSize = ImGui::GetWindowSize();

	ImGui::GetWindowDrawList()->AddImage(textureId, pos,
										 ImVec2(pos.x + m_SceneSize.x, pos.y + m_SceneSize.y), ImVec2(0, 1),
										 ImVec2(1, 0));

	ImGui::End();
}

void Editor::renderPropertyWindow()
{
	static float f = 0.0f;
	static int counter = 0;

	ImGui::Begin("Hello, world!");
	ImGui::Text("This is some useful text.");
	ImGui::Checkbox("Demo Window", &m_ShowDemoWindow);
	ImGui::Checkbox("Another Window", &m_ShowAnotherWindow);

	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
	ImGui::ColorEdit3("clear color", reinterpret_cast<float *>(&m_ClearColor));

	if (ImGui::Button("Button"))
	{
		counter++;
	}

	ImGui::SameLine();
	ImGui::Text("counter = %d", counter);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
				ImGui::GetIO().Framerate);
	ImGui::End();
}

std::pair<int, int> Editor::getSceneWindowSize() const
{
	return {m_SceneSize.x, m_SceneSize.y};
}

void Editor::setColorStyle()
{
	ImGuiStyle *style = &ImGui::GetStyle();
	ImVec4 *colors = style->Colors;

	colors[ImGuiCol_TitleBgActive] = ImVec4(0.14f, 0.14f, 0.14f, 0.87f);

	colors[ImGuiCol_Tab] = ImVec4(0.1f, 0.07f, 0.1f, 1.0f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.13f, 0.1f, 0.13f, 0.8f);
	colors[ImGuiCol_TabActive] = ImVec4(0.306f, 0.32f, 0.329f, 1);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.2f, 0.2f, 0.2f, 0.8f);
}
