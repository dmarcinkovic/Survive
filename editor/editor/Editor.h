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
#include "SkyboxWindow.h"
#include "FileChooser.h"
#include "CameraWindow.h"
#include "EventHandler.h"
#include "EditorUtil.h"
#include "Log.h"
#include "SceneSerializer.h"
#include "EntityManager.h"
#include "Camera.h"
#include "Gizmos.h"
#include "Loader.h"
#include "Scene.h"
#include "StatusBar.h"

namespace Survive
{
	enum class PropertyWindow
	{
		ENTITY, CAMERA, NONE
	};

	class Editor
	{
	private:
		Loader m_Loader;

		Scene m_Scene;

		FileChooser m_OpenWindow;
		FileChooser m_SaveWindow;

		EntityManager m_Manager{};
		ContentBrowser m_ContentBrowser{};

		Log m_Log;
		StatusBar m_StatusBar;

		bool m_OpenDialog{}, m_SaveDialog{}, m_SaveAsDialog{};

		SkyboxWindow m_SkyWindow;
		bool m_SkyboxDialog = false;

		SceneSerializer m_SceneLoader;
		EditorUtil m_EditorUtil;

		std::string m_SavedFile;
		PropertyWindow m_DrawingWindow = PropertyWindow::NONE;

	public:
		explicit Editor(Renderer &renderer);

		void render(entt::registry &registry, Renderer &renderer, Camera &camera);

		static void dock();

		static void newFrame();

		void handleKeyEvents(const EventHandler &eventHandler);

		static float getSceneWidth();

		static float getSceneHeight();

		static std::pair<float, float> getScenePosition();

		static std::pair<float, float> getSceneRegionMin();

		static bool isSceneFocused();

		[[nodiscard]] bool isScenePlaying() const;

		void addPlayButtonListener(const ButtonListener &listener);

		void addReloadButtonListener(const ButtonListener &listener);

	private:
		void renderPropertyWindow(entt::registry &registry, Camera &camera);

		void renderMenu();

		void renderOpenDialog(entt::registry &registry);

		void renderSaveAsDialog(entt::registry &registry);

		void renderSaveDialog(entt::registry &registry);

		static void setColorStyle();

		void handleMouseDragging(entt::registry &registry, Renderer &renderer, const Camera &camera);
	};
}


#endif //SURVIVE_EDITOR_H
