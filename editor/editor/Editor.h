//
// Created by david on 31. 12. 2020..
//

#ifndef SURVIVE_EDITOR_H
#define SURVIVE_EDITOR_H

#include <imgui.h>
#include <utility>
#include <ImGuizmo.h>
#include <functional>

#include "ContentBrowser.h"
#include "EventHandler.h"
#include "LogEditor.h"
#include "SceneSerializer.h"
#include "EntityManager.h"
#include "Camera.h"
#include "Loader.h"
#include "Scene.h"
#include "StatusBar.h"
#include "PropertyWindow.h"
#include "Menu.h"
#include "EditorEventHandler.h"

namespace Survive
{
	class Editor
	{
	private:
		Loader m_Loader;

		Scene m_Scene;
		Menu m_Menu;

		EntityManager m_Manager{};
		ContentBrowser m_ContentBrowser{};

		LogEditor m_Log;
		StatusBar m_StatusBar;

		SceneSerializer m_SceneLoader;

		std::string m_SavedFile;
		PropertyWindow m_DrawingWindow = PropertyWindow::NONE;

		EditorEventHandler m_EventHandler;

	public:
		explicit Editor(Renderer &renderer);

		~Editor();

		void render(entt::registry &registry, Renderer &renderer, Camera &camera);

		static void dock();

		static void newFrame();

		void handleKeyEvents(const EventHandler &eventHandler);

		void handleMouseDragging(entt::registry &registry, Renderer &renderer, const Camera &camera);

		[[nodiscard]] bool isScenePlaying() const;

		void addPlayButtonListener(const ButtonListener &listener);

		void addReloadButtonListener(const ButtonListener &listener);

	private:
		void renderPropertyWindow(entt::registry &registry, Camera &camera);

		static void setColorStyle();

		void drawMenu(entt::registry &registry, Renderer &renderer);

		static void renderDebugWindow();
	};
}


#endif //SURVIVE_EDITOR_H
