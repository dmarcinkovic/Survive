//
// Created by david on 14. 03. 2022..
//

#ifndef SURVIVE_EDITOREVENTHANDLER_H
#define SURVIVE_EDITOREVENTHANDLER_H

#include "entt.hpp"
#include "Camera.h"
#include "Renderer.h"
#include "ContentBrowser.h"
#include "EntityManager.h"
#include "SceneSerializer.h"

namespace Survive
{
	class EditorEventHandler
	{
	private:
		ContentBrowser &m_ContentBrowser;
		EntityManager &m_Manager;

		SceneSerializer &m_SceneLoader;

	public:
		EditorEventHandler(ContentBrowser &contentBrowser, EntityManager &manager, SceneSerializer &sceneLoader);

		void handleMouseDragging(entt::registry &registry, Renderer &renderer, Loader &loader, const Camera &camera,
								 std::string &savedFile);

	private:
		void loadScene(entt::registry &registry, std::string &savedFile, const std::filesystem::path &file);

		static void
		loadModel(entt::registry &registry, Loader &loader, const std::filesystem::path &file, const Camera &camera);

		static void
		loadTexture(entt::registry &registry, Renderer &renderer, const std::filesystem::path &file, Loader &loader);
	};
}

#endif //SURVIVE_EDITOREVENTHANDLER_H
