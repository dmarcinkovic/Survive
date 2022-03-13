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

Survive::Editor::~Editor()
{
	ImGui::PopStyleColor(6);
}

void Survive::Editor::render(entt::registry &registry, Renderer &renderer, Camera &camera)
{
	renderPropertyWindow(registry, camera);
	m_Scene.renderSceneWindow(camera, renderer, registry,
							  m_Manager.getSelectedEntity(), m_StatusBar.isScenePlaying());
	m_StatusBar.draw();

	drawMenu(registry, renderer);

	m_Log.drawLogWindow();
	m_ContentBrowser.draw();

	renderDebugWindow();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	camera.recalculateProjectionMatrix(Scene::getSceneWidth(), Scene::getSceneHeight());
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
	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.14f, 0.14f, 0.14f, 1.0f));

	ImGui::PushStyleColor(ImGuiCol_Tab, ImVec4(0.1f, 0.07f, 0.1f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_TabHovered, ImVec4(0.13f, 0.1f, 0.13f, 0.8f));
	ImGui::PushStyleColor(ImGuiCol_TabActive, ImVec4(0.306f, 0.32f, 0.329f, 1));
	ImGui::PushStyleColor(ImGuiCol_TabUnfocused, ImVec4(0.25f, 0.25f, 0.25f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_TabUnfocusedActive, ImVec4(0.2f, 0.2f, 0.2f, 0.8f));
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

					try
					{
						m_SceneLoader.loadScene(registry, file.string());
						m_SavedFile = file.string();

						Log::logMessage(LogType::INFO, "Scene loaded successfully");
					} catch (const std::exception &exception)
					{
						Log::logMessage(LogType::ERROR, "Failed to load the scene");
					}
				} else if (extension == ".obj" && file.has_stem())
				{
					auto[x, y] = Scene::getScenePosition();
					float width = Scene::getSceneWidth();
					float height = Scene::getSceneHeight();
					EditorUtil::loadDraggedModels(registry, m_Loader, file, camera, x, y, width, height);
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

void Survive::Editor::renderDebugWindow()
{
	if (ImGui::Begin("Debug"))
	{
		ImGui::Text("Application average %.1f FPS", ImGui::GetIO().Framerate);
	}
	ImGui::End();
}
