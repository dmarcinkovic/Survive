//
// Created by david on 17. 10. 2021..
//

#ifndef SURVIVE_APPLICATION_H
#define SURVIVE_APPLICATION_H

#include <memory>
#include <box2d/box2d.h>

#include "entt.hpp"
#include "Editor.h"
#include "EventHandler.h"
#include "Loader.h"
#include "Camera.h"
#include "Light.h"
#include "Renderer.h"
#include "Display.h"
#include "Components.h"
#include "RegistryUtil.h"

namespace Survive
{
	class Application
	{
	private:
		const b2Vec2 m_Gravity{0.0f, -9.81f};

		Display m_Display;
		Loader m_Loader;

		Camera m_Camera;
		Light m_Light;
		Renderer m_Renderer;

		Editor m_Editor;
		EventHandler m_EventHandler;

		std::unique_ptr<b2World> m_World;
		entt::registry m_Registry;

		bool m_PlayScene{};

		RegistryUtil m_RegistryUtil;

		DaeParser m_DaeParser;

	public:
		Application(int windowWidth, int windowHeight, const char *title);

		void run();
	};
}

#endif //SURVIVE_APPLICATION_H
