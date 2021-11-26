//
// Created by david on 31. 12. 2020..
//


#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <imgui_internal.h>

#include "Key.h"
#include "Editor.h"

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
	renderMenu();
	m_StatusBar.draw();

	handleMouseDragging(registry, renderer, camera);

	renderOpenDialog(registry);
	renderSaveAsDialog(registry);
	renderSaveDialog(registry);
	m_SkyWindow.draw(registry, renderer, m_SkyboxDialog);

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

			if (ImGui::MenuItem("Camera", "", nullptr))
			{
				m_DrawingWindow = PropertyWindow::CAMERA;
				m_Manager.stopDrawing();
			}

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
			std::string file = m_OpenWindow.getSelectedFile().string();
			if (!file.empty())
			{
				if (file.ends_with(".survive"))
				{
					m_Manager.setSelectedEntity(-1);
					m_SceneLoader.loadScene(registry, file);
					m_SavedFile = file;
				} else
				{
					Log::logWindow(LogType::ERROR, "Cannot load scene from " + file);
				}
			}
		}
	}
}

void Survive::Editor::renderSaveAsDialog(entt::registry &registry)
{
	if (m_SaveAsDialog)
	{
		m_SaveWindow.save(600.0f, 400.0f, &m_SaveAsDialog);

		if (!m_SaveAsDialog)
		{
			std::string selectedFile = m_SaveWindow.getSelectedFile().string();
			if (!selectedFile.empty())
			{
				m_SavedFile = std::move(selectedFile);
			}

			if (!m_SavedFile.empty())
			{
				SceneSerializer::saveScene(registry, m_SavedFile);
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
			SceneSerializer::saveScene(registry, m_SavedFile);
		}

		m_SaveDialog = false;
	}
}

void Survive::Editor::handleKeyEvents(const EventHandler &eventHandler)
{
	if (eventHandler.isKeyControlPressed() && eventHandler.isKeyPressed(Key::O))
	{
		m_OpenDialog = true;
	} else if (eventHandler.isShiftKeyPressed() && eventHandler.isKeyControlPressed() &&
			   eventHandler.isKeyPressed(Key::S))
	{
		m_SaveAsDialog = true;
	} else if (eventHandler.isKeyControlPressed() &&
			   eventHandler.isKeyPressed(Key::S))
	{
		m_SaveDialog = true;
	}

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
