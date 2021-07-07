//
// Created by david on 31. 12. 2020..
//

#ifndef SURVIVE_EDITOR_H
#define SURVIVE_EDITOR_H

#include <imgui.h>
#include <utility>

#include "FileChooser.h"
#include "EventHandler.h"
#include "Log.h"
#include "SceneLoader.h"
#include "EntityManager.h"

namespace Survive
{
	class Editor
	{
	private:
		ImGuiIO &m_Io;
		GLuint m_Scene;
		ImVec2 m_SceneSize;

		FileChooser m_FileChooser;
		EntityManager m_Manager{};

		bool m_OpenDialog = false;
		bool m_SaveDialog = false;
		bool m_SaveAsDialog = false;

		SceneLoader m_SceneLoader;
		bool m_IsSceneWindowFocused = true;

		std::string m_SavedFile;

	public:
		explicit Editor(GLuint scene);

		void render(entt::registry &registry);

		static void dock();

		static void newFrame();

		void handleKeyEvents(const EventHandler &eventHandler);

		bool &isSceneWindowFocused();

	private:
		void renderSceneWindow();

		void renderPropertyWindow(entt::registry &registry);

		void renderMenu();

		void renderOpenDialog(entt::registry &registry);

		void renderSaveAsDialog(entt::registry &registry);

		void renderSaveDialog(entt::registry &registry);

		static void setColorStyle();
	};
}


#endif //SURVIVE_EDITOR_H
