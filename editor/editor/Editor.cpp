//
// Created by david on 31. 12. 2020..
//


#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include "Key.h"
#include "Editor.h"

float Survive::Editor::m_SceneWidth{};
float Survive::Editor::m_SceneHeight{};
float Survive::Editor::m_ScenePosX{};
float Survive::Editor::m_ScenePosY{};
float Survive::Editor::m_SceneRegionX{};
float Survive::Editor::m_SceneRegionY{};

bool Survive::Editor::m_SceneFocused{};

Survive::Editor::Editor(Renderer &renderer)
		: m_Io(ImGui::GetIO()), m_Scene(renderer.getRenderedTexture())
{
	m_Io.ConfigFlags = m_Io.ConfigFlags | ImGuiConfigFlags_DockingEnable |
					   ImGuiWindowFlags_UnsavedDocument;

	m_Io.ConfigWindowsMoveFromTitleBarOnly = true;
	renderer.addMousePickingListener([this](int selectedEntity) {
		m_Manager.setSelectedEntity(selectedEntity);
	});

	setColorStyle();
}

void Survive::Editor::render(entt::registry &registry, Renderer &renderer, Camera &camera)
{
	renderPropertyWindow(registry);
	renderSceneWindow(camera, registry);
	renderMenu();

	handleMouseDragging(registry, renderer);

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

	camera.recalculateProjectionMatrix(m_SceneWidth, m_SceneHeight);
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

void Survive::Editor::renderSceneWindow(const Camera &camera, entt::registry &registry)
{
	if (ImGui::Begin("Scene window"))
	{
		m_IsSceneWindowFocused = ImGui::IsWindowFocused() && ImGui::IsWindowHovered();

		ImVec2 pos = ImGui::GetCursorScreenPos();
		m_ScenePosX = pos.x;
		m_ScenePosY = pos.y;

		m_SceneRegionX = ImGui::GetWindowContentRegionMin().x;
		m_SceneRegionY = ImGui::GetWindowContentRegionMin().y;

		auto textureId = reinterpret_cast<ImTextureID>(m_Scene);

		m_SceneWidth = ImGui::GetWindowWidth();
		m_SceneHeight = ImGui::GetWindowHeight();

		ImGui::GetWindowDrawList()->AddImage(textureId, pos,
											 ImVec2(pos.x + m_SceneWidth, pos.y + m_SceneHeight), ImVec2(0, 1),
											 ImVec2(1, 0));

		m_Gizmos.setRect(pos.x, pos.y, m_SceneWidth, m_SceneHeight);
		m_Gizmos.draw(registry, camera, m_Manager.getSelectedEntity());

		m_SceneFocused = !ImGui::IsPopupOpen("", ImGuiPopupFlags_AnyPopupId | ImGuiPopupFlags_AnyPopupLevel);
	}

	ImGui::End();
}

void Survive::Editor::renderPropertyWindow(entt::registry &registry)
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
//				m_CameraWindow.draw();
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
				m_Manager.setSelectedEntity(-1);
				m_SceneLoader.loadScene(registry, file);
				m_SavedFile = file;
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
			std::string selectedFile = m_SaveWindow.getSelectedFile().string();
			if (!selectedFile.empty())
			{
				m_SavedFile = std::move(selectedFile);
			}

			if (!m_SavedFile.empty())
			{
				Survive::SceneSerializer::saveScene(registry, m_SavedFile);
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
			Survive::SceneSerializer::saveScene(registry, m_SavedFile);
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
		m_Gizmos.handleKeyEvents(eventHandler);
	}
}

float Survive::Editor::getSceneWidth()
{
	return m_SceneWidth;
}

float Survive::Editor::getSceneHeight()
{
	return m_SceneHeight;
}

std::pair<float, float> Survive::Editor::getScenePosition()
{
	return {m_ScenePosX, m_ScenePosY};
}

bool Survive::Editor::isSceneFocused()
{
	return m_SceneFocused;
}

void Survive::Editor::handleMouseDragging(entt::registry &registry, Renderer &renderer)
{
	if (!ImGui::IsMouseDragging(ImGuiMouseButton_Left) && m_ContentBrowser.startedDragging())
	{
		if (isInsideScene())
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
					m_EditorUtil.loadDraggedModels(registry, file);
				} else if (extension == ".png" || extension == ".jpg" || extension == ".jpeg")
				{
					renderer.setMousePickingPosition(ImGui::GetMousePos().x, ImGui::GetMousePos().y);
					EditorUtil::registerListener(registry, renderer, file);
				}
			}
		}

		m_ContentBrowser.stopDragging();
	}
}

bool Survive::Editor::isInsideScene()
{
	float x = ImGui::GetMousePos().x;
	float y = ImGui::GetMousePos().y;

	return x >= m_ScenePosX && x <= m_ScenePosX + m_SceneWidth &&
		   y >= m_ScenePosY && y <= m_ScenePosY + m_SceneHeight;
}

std::pair<float, float> Survive::Editor::getSceneRegionMin()
{
	return {m_SceneRegionX, m_SceneRegionY};
}
