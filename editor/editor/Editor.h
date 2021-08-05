//
// Created by david on 31. 12. 2020..
//

#ifndef SURVIVE_EDITOR_H
#define SURVIVE_EDITOR_H

#include <imgui.h>
#include <utility>
#include <ImGuizmo.h>

#include "SkyboxWindow.h"
#include "FileChooser.h"
#include "EventHandler.h"
#include "Log.h"
#include "SceneSerializer.h"
#include "EntityManager.h"
#include "Camera.h"
#include "Gizmos.h"

namespace Survive
{
	class Editor
	{
	private:
		static float m_SceneWidth;
		static float m_SceneHeight;

		ImGuiIO &m_Io;
		GLuint m_Scene;

		FileChooser m_OpenWindow;
		FileChooser m_SaveWindow;
		EntityManager m_Manager{};
		Gizmos m_Gizmos;

		bool m_OpenDialog = false;
		bool m_SaveDialog = false;
		bool m_SaveAsDialog = false;

		SkyboxWindow m_SkyWindow;
		bool m_SkyboxDialog = false;

		SceneSerializer m_SceneLoader;
		bool m_IsSceneWindowFocused = true;

		std::string m_SavedFile;

	public:
		explicit Editor(GLuint scene);

		void render(entt::registry &registry, Renderer &renderer, Camera &camera);

		static void dock();

		static void newFrame();

		void handleKeyEvents(const EventHandler &eventHandler);

		bool &isSceneWindowFocused();

		static float getSceneWidth();

		static float getSceneHeight();

	private:
		void renderSceneWindow(const Camera &camera, entt::registry &registry);

		void renderPropertyWindow(entt::registry &registry);

		void renderMenu();

		void renderOpenDialog(entt::registry &registry);

		void renderSaveAsDialog(entt::registry &registry);

		void renderSaveDialog(entt::registry &registry);

		static void setColorStyle();
	};
}


#endif //SURVIVE_EDITOR_H
