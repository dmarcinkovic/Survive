//
// Created by david on 26. 11. 2021..
//

#ifndef SURVIVE_SCENE_H
#define SURVIVE_SCENE_H

#include <utility>

#include "entt.hpp"
#include "Camera.h"
#include "Renderer.h"
#include "Gizmos.h"
#include "EventHandler.h"

namespace Survive
{
	class Scene
	{
	private:
		static float m_SceneWidth;
		static float m_SceneHeight;
		static float m_ScenePosX, m_ScenePosY;
		static float m_SceneRegionX, m_SceneRegionY;
		static bool m_SceneFocused;

		Texture m_Scene;
		Gizmos m_Gizmos;

	public:
		explicit Scene(const Texture &scene);

		void renderSceneWindow(Camera &camera, Renderer &renderer, entt::registry &registry,
							   entt::entity selectedEntity, bool isScenePlaying);

		static float getSceneWidth();

		static float getSceneHeight();

		static std::pair<float, float> getScenePosition();

		static std::pair<float, float> getSceneRegionMin();

		static bool isSceneFocused();

		static bool isInsideScene();

		void handleKeyEvents(const EventHandler &eventHandler);

	private:
		static void collectSceneData();
	};
}

#endif //SURVIVE_SCENE_H
