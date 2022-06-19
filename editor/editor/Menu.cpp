//
// Created by david on 26. 11. 2021..
//

#include "Menu.h"
#include "Log.h"

void Survive::Menu::renderMenu(EntityManager &manager, PropertyWindow &drawingWindow)
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
			if (ImGui::MenuItem("Camera", "", nullptr))
			{
				drawingWindow = PropertyWindow::CAMERA;
				manager.stopDrawing();
			}

			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
}

void Survive::Menu::handleKeyEvents(const EventHandler &eventHandler)
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
}

void Survive::Menu::renderSaveDialog(entt::registry &registry, std::string &savedFile)
{
	if (m_SaveDialog)
	{
		if (savedFile.empty())
		{
			m_SaveAsDialog = true;
		} else
		{
			SceneSerializer::saveScene(registry, savedFile);
		}

		m_SaveDialog = false;
	}
}

void Survive::Menu::renderSaveAsDialog(entt::registry &registry, std::string &savedFile)
{
	if (m_SaveAsDialog)
	{
		m_SaveWindow.open(600.0f, 400.0f, &m_SaveAsDialog);

		if (!m_SaveAsDialog)
		{
			std::string selectedFile = m_SaveWindow.getSelectedFile().string();
			if (!selectedFile.empty())
			{
				savedFile = std::move(selectedFile);
			}

			if (!savedFile.empty())
			{
				SceneSerializer::saveScene(registry, savedFile);
			}
		}
	}
}

void Survive::Menu::renderOpenDialog(entt::registry &registry, EntityManager &manager, SceneSerializer &sceneLoader,
									 std::string &savedFile)
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
					manager.setSelectedEntity(registry, -1);
					loadScene(registry, sceneLoader, savedFile, file);
				} else
				{
					Log::logMessage(LogType::ERROR, "Cannot load scene from " + file);
				}
			}
		}
	}
}

void Survive::Menu::loadScene(entt::registry &registry, Survive::SceneSerializer &sceneLoader, std::string &savedFile,
							  const std::string &file)
try
{
	sceneLoader.loadScene(registry, file);
	savedFile = file;

	Log::logMessage(LogType::INFO, "Successfully loaded the scene");
} catch (const std::exception &exception)
{
	Log::logMessage(LogType::ERROR, "Failed to load the scene");
}
