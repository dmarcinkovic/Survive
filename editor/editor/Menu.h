//
// Created by david on 26. 11. 2021..
//

#ifndef SURVIVE_MENU_H
#define SURVIVE_MENU_H

#include <functional>
#include <vector>

#include "SaveDialog.h"
#include "OpenDialog.h"
#include "EntityManager.h"
#include "SceneSerializer.h"
#include "EventHandler.h"
#include "PropertyWindow.h"
#include "SkyboxWindow.h"

namespace Survive
{
	class Menu
	{
	private:
		OpenDialog m_OpenWindow;
		SaveDialog m_SaveWindow;

		bool m_OpenDialog{}, m_SaveDialog{}, m_SaveAsDialog{};
		bool m_SkyboxDialog = false;

		SkyboxWindow m_SkyWindow;

	public:
		void renderMenu(EntityManager &manager, PropertyWindow &drawingWindow);

		void renderOpenDialog(entt::registry &registry, EntityManager &manager,
							  SceneSerializer &sceneLoader, std::string &savedFile);

		void handleKeyEvents(const EventHandler &eventHandler);

		void renderSaveDialog(entt::registry &registry, std::string &savedFile);

		void renderSaveAsDialog(entt::registry &registry, std::string &savedFile);

		void drawSkyboxWindow(entt::registry &registry, Renderer &renderer);

	private:
		static void loadScene(entt::registry &registry, SceneSerializer &sceneLoader, std::string &savedFile,
							  const std::string &file);
	};
}


#endif //SURVIVE_MENU_H
