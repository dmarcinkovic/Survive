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

namespace Survive
{
	enum class PropertyWindow
	{
		ENTITY, CAMERA, NONE
	};

	using ButtonListener = std::function<void()>;

	class Editor
	{
	private:
		static float m_SceneWidth;
		static float m_SceneHeight;
		static float m_ScenePosX, m_ScenePosY;
		static float m_SceneRegionX, m_SceneRegionY;
		static bool m_SceneFocused;

		Loader m_Loader;

		GLuint m_Scene;

		FileChooser m_OpenWindow;
		FileChooser m_SaveWindow;

		EntityManager m_Manager{};
		Gizmos m_Gizmos;
		ContentBrowser m_ContentBrowser{};

		Log m_Log;

		bool m_OpenDialog{}, m_SaveDialog{}, m_SaveAsDialog{};
		Texture m_PlayButton, m_ReloadButton;
		bool m_IsScenePlaying{};

		SkyboxWindow m_SkyWindow;
		bool m_SkyboxDialog = false;

		SceneSerializer m_SceneLoader;
		EditorUtil m_EditorUtil;

		std::string m_SavedFile;
		PropertyWindow m_DrawingWindow = PropertyWindow::NONE;

		std::vector<ButtonListener> m_PlayButtonListeners;
		std::vector<ButtonListener> m_ReloadButtonListeners;

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
		void renderSceneWindow(Camera &camera, Renderer &renderer, entt::registry &registry);

		void renderPropertyWindow(entt::registry &registry, Camera &camera);

		void renderMenu();

		void renderOpenDialog(entt::registry &registry);

		void renderSaveAsDialog(entt::registry &registry);

		void renderSaveDialog(entt::registry &registry);

		static void setColorStyle();

		void handleMouseDragging(entt::registry &registry, Renderer &renderer, const Camera &camera);

		static bool isInsideScene();

		void drawStatusBar();

		void drawPlayAndPauseButtons(float buttonSize);

		static void setPlayButtonColorStyle();

		static void collectSceneData();

		static void notifyListeners(const std::vector<ButtonListener> &listeners);

		static bool drawImageButton(const Texture &image, bool disabled, const ImVec2 &buttonSize,
							   const std::vector<ButtonListener> &buttonListener, const char *tooltipText);
	};
}


#endif //SURVIVE_EDITOR_H
