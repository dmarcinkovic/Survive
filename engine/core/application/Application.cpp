//
// Created by david on 17. 10. 2021..
//

#include "Application.h"
#include "System.h"
#include "ContactListener.h"

Survive::Application::Application(int windowWidth, int windowHeight, const char *title)
		: m_Display(windowWidth, windowHeight, title), m_Light(glm::vec3{100.0f}, glm::vec3{1.0f}),
		  m_Renderer(m_Light), m_Editor(m_Renderer), m_World(std::make_unique<b2World>(m_Gravity))
{
	auto cube = m_Registry.create();
	m_Registry.emplace<TagComponent>(cube, "cube");
	m_Registry.emplace<Transform3DComponent>(cube, glm::vec3{0, 0, -8}, glm::vec3{1}, glm::vec3{35, 40, 0});
	m_Registry.emplace<Render3DComponent>(cube, TexturedModel(ObjParser::loadObj("assets/models/cube.obj", m_Loader),
															  Texture()));
	m_Registry.emplace<SpriteComponent>(cube, glm::vec4{0.5f, 0.5f, 0.8f, 1.0f});

	m_ContactListener = std::make_unique<ContactListener>(m_Registry);

	m_Editor.addPlayButtonListener([&]() {
		m_RegistryUtil.store<RigidBody2DComponent, SpriteSheetComponent>(m_Registry);
		System::init(m_Registry, m_EventHandler, m_World.get());
		m_World->SetContactListener(m_ContactListener.get());
	});

	m_Editor.addReloadButtonListener([this]() {
		m_RegistryUtil.restore<RigidBody2DComponent, SpriteSheetComponent>(m_Registry);
		m_World = std::make_unique<b2World>(m_Gravity);
		System::destroy(m_Registry);
	});
}

void Survive::Application::run()
{
	while (m_Display.isRunning())
	{
		Display::clearWindow();

		m_Editor.handleKeyEvents(m_EventHandler);
		m_Editor.handleMouseDragging(m_Registry, m_Renderer, m_Camera);

		Editor::newFrame();
		Editor::dock();
		m_Editor.render(m_Registry, m_Renderer, m_Camera);

		if (m_Editor.isScenePlaying())
		{
			System::update(m_Registry, m_World.get());
		}

		m_Display.update();
	}
}
