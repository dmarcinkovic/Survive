//
// Created by david on 31. 12. 2020..
//


#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <imgui_internal.h>

#include "Editor.h"
#include "CameraWindow.h"

Survive::Editor::Editor(Renderer &renderer)
		: m_Scene(renderer.getRenderedTexture())
{
	ImGuiIO &io = ImGui::GetIO();
	io.ConfigFlags = io.ConfigFlags | ImGuiConfigFlags_DockingEnable |
					 ImGuiWindowFlags_UnsavedDocument;

	io.ConfigWindowsMoveFromTitleBarOnly = true;
	renderer.addMousePickingListener([this](int selectedEntity) {
		m_Manager.setSelectedEntity(selectedEntity);
	});

	setColorStyle();
}

void Survive::Editor::render(entt::registry &registry, Renderer &renderer, Camera &camera)
{
	renderPropertyWindow(registry, camera);
	m_Scene.renderSceneWindow(camera, renderer, registry, m_Manager.getSelectedEntity(), m_StatusBar.isScenePlaying());
	m_StatusBar.draw();

	handleMouseDragging(registry, renderer, camera);

	drawMenu(registry, renderer);

	m_Log.drawLogWindow();
	m_ContentBrowser.draw();

	if (ImGui::Begin("Debug"))
	{
		ImGui::Text("Application average %.1f FPS", ImGui::GetIO().Framerate);
	}
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	float width = Scene::getSceneWidth();
	float height = Scene::getSceneHeight();
	camera.recalculateProjectionMatrix(width, height);
}

void Survive::Editor::newFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	Gizmos::newFrame();
}

void Survive::Editor::dock()
{
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
}

void Survive::Editor::renderPropertyWindow(entt::registry &registry, Camera &camera)
{
	if (ImGui::Begin("Scene hierarchy"))
	{
		if (m_Manager.addEntity(registry))
		{
			m_DrawingWindow = PropertyWindow::ENTITY;
		}
	}

	ImGui::End();

	if (ImGui::Begin("Property panel"))
	{
		switch (m_DrawingWindow)
		{
			case PropertyWindow::ENTITY:
				m_Manager.drawPropertyPanel(registry);
				break;
			case PropertyWindow::CAMERA:
				CameraWindow::draw(camera);
				break;
			default:
				break;
		}
	}

	ImGui::End();
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

void Survive::Editor::handleKeyEvents(const EventHandler &eventHandler)
{
	m_Menu.handleKeyEvents(eventHandler);

	if (!m_Manager.isFocused() && !m_ContentBrowser.isUsingKeyEvents())
	{
		m_Manager.handleKeyEvents(eventHandler);
		m_Scene.handleKeyEvents(eventHandler);
	}
}

float Survive::Editor::getSceneWidth()
{
	return Scene::getSceneWidth();
}

float Survive::Editor::getSceneHeight()
{
	return Scene::getSceneHeight();
}

std::pair<float, float> Survive::Editor::getScenePosition()
{
	return Scene::getScenePosition();
}

bool Survive::Editor::isSceneFocused()
{
	return Scene::isSceneFocused();
}

void Survive::Editor::handleMouseDragging(entt::registry &registry, Renderer &renderer, const Camera &camera)
{
	if (!ImGui::IsMouseDragging(ImGuiMouseButton_Left) && m_ContentBrowser.startedDragging())
	{
		if (Scene::isInsideScene())
		{
			std::filesystem::path file = m_ContentBrowser.getDraggedFile();

			if (file.has_extension())
			{
				std::string extension = file.extension().string();

				if (extension == ".survive")
				{
					m_Manager.setSelectedEntity(-1);
					m_SceneLoader.loadScene(registry, file.string());
					m_SavedFile = file.string();
				} else if (extension == ".obj" && file.has_stem())
				{
					auto[x, y] = Scene::getScenePosition();
					float width = Scene::getSceneWidth();
					float height = Scene::getSceneHeight();
					m_EditorUtil.loadDraggedModels(registry, file, camera, x, y, width, height);
				} else if (extension == ".png" || extension == ".jpg" || extension == ".jpeg")
				{
					renderer.setMousePickingPosition(ImGui::GetMousePos().x, ImGui::GetMousePos().y);
					EditorUtil::registerListener(registry, renderer, file, m_Loader);
				}
			}
		}

		m_ContentBrowser.stopDragging();
	}
}

std::pair<float, float> Survive::Editor::getSceneRegionMin()
{
	return Scene::getSceneRegionMin();
}

bool Survive::Editor::isScenePlaying() const
{
	return m_StatusBar.isScenePlaying();
}

void Survive::Editor::addPlayButtonListener(const ButtonListener &listener)
{
	m_StatusBar.addPlayButtonListener(listener);
}

void Survive::Editor::addReloadButtonListener(const ButtonListener &listener)
{
	m_StatusBar.addReloadButtonListener(listener);
}

void Survive::Editor::drawMenu(entt::registry &registry, Renderer &renderer)
{
	m_Menu.renderMenu(m_Manager, m_DrawingWindow);

	m_Menu.renderOpenDialog(registry, m_Manager, m_SceneLoader, m_SavedFile);
	m_Menu.renderSaveAsDialog(registry, m_SavedFile);
	m_Menu.renderSaveDialog(registry, m_SavedFile);

	m_Menu.drawSkyboxWindow(registry, renderer);
}
