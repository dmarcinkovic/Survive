//
// Created by david on 17. 10. 2021..
//

#include "Application.h"
#include "PhysicSystem.h"

Survive::Application::Application(int windowWidth, int windowHeight, const char *title)
		: m_Display(windowWidth, windowHeight, title), m_Light(glm::vec3{100.0f}, glm::vec3{1.0f}),
		  m_Renderer(m_Light), m_Editor(m_Renderer), m_World(std::make_unique<b2World>(m_Gravity))
{
	auto rectangle = m_Registry.create();
	m_Registry.emplace<TagComponent>(rectangle, "rectangle");
	m_Registry.emplace<Transform3DComponent>(rectangle, glm::vec3{0, 0.7f, 0}, glm::vec3{0.25f, 0.25f, 1.0f});
	m_Registry.emplace<Render2DComponent>(rectangle,
										TexturedModel(m_Loader.renderQuad(), Loader::loadTexture("res/rectangle.png")));
	m_Registry.emplace<RigidBody2DComponent>(rectangle, b2_dynamicBody);
	m_Registry.emplace<BoxCollider2DComponent>(rectangle, 0.25f * 10.0f, 0.25f * 10.0f, 1.0f, 0.3f, 0.5f);

	auto ground = m_Registry.create();
	m_Registry.emplace<TagComponent>(ground, "ground");
	Transform3DComponent groundPos(glm::vec3{-0.55f, -0.8f, 0}, glm::vec3{0.4f, 0.05f, 1.0f});
	m_Registry.emplace<Transform3DComponent>(ground, groundPos);
	m_Registry.emplace<Render2DComponent>(ground,
										TexturedModel(m_Loader.renderQuad(), Loader::loadTexture("res/dirt.png")));
	m_Registry.emplace<RigidBody2DComponent>(ground, b2_staticBody);
	m_Registry.emplace<BoxCollider2DComponent>(ground, 0.4f * 10.0f, 0.05f * 10.0f, 1.0f, 0.3f, 0.5f);

	PhysicSystem::init(m_Registry, m_World.get());
}

void Survive::Application::run()
{
	while(m_Display.isRunning())
	{
		Display::clearWindow();

		m_Editor.handleKeyEvents(m_EventHandler);

		Editor::newFrame();
		Editor::dock();
		m_Editor.render(m_Registry, m_Renderer, m_Camera);

		m_Renderer.renderScene(m_Registry, m_Camera, true);

		PhysicSystem::update(m_Registry);

		float frameRate = ImGui::GetIO().Framerate;
		m_World->Step(1.0f / frameRate, 5, 5);

		m_Display.update();
	}
}
