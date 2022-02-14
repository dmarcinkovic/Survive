//
// Created by david on 17. 10. 2021..
//

#include "Application.h"
#include "System.h"
#include "PhysicSystem.h"

Survive::Application::Application(int windowWidth, int windowHeight, const char *title)
		: m_Display(windowWidth, windowHeight, title), m_Light(glm::vec3{100.0f}, glm::vec3{1.0f}),
		  m_Renderer(m_Light), m_Editor(m_Renderer), m_World(std::make_unique<b2World>(m_Gravity))
{
	auto box = m_Registry.create();
	m_Registry.emplace<TagComponent>(box, "box");
	m_Registry.emplace<Transform3DComponent>(box, glm::vec3{0, 0.7f, 0}, glm::vec3{0.25f, 0.25f, 1.0f});
	m_Registry.emplace<Render2DComponent>(box,
										  TexturedModel(m_Loader.renderQuad(),
														m_Loader.loadTexture("assets/textures/rectangle.png")));
	m_Registry.emplace<RigidBody2DComponent>(box, b2_dynamicBody);
	m_Registry.emplace<BoxCollider2DComponent>(box, 2.5f, 2.5f, 1.0f, 0.3f, 0.5f);

	auto ground2 = m_Registry.create();
	m_Registry.emplace<TagComponent>(ground2, "ground2");
	m_Registry.emplace<Transform3DComponent>(ground2, glm::vec3{0, -0.7f, 0}, glm::vec3{0.4f, 0.05f, 1.0f});
	m_Registry.emplace<Render2DComponent>(ground2, TexturedModel(m_Loader.renderQuad(),
																 m_Loader.loadTexture("assets/textures/dirt.png")));
	m_Registry.emplace<RigidBody2DComponent>(ground2, b2_dynamicBody);
	m_Registry.emplace<BoxCollider2DComponent>(ground2, 4, 0.5f, 1.0f, 0.3, 0.5);

	auto ground = m_Registry.create();
	m_Registry.emplace<TagComponent>(ground, "ground");
	m_Registry.emplace<Transform3DComponent>(ground, glm::vec3{0, -0.13f, 0}, glm::vec3{0.05f, 0.3f, 1.0f});
	m_Registry.emplace<Render2DComponent>(ground,
										  TexturedModel(m_Loader.renderQuad(),
														m_Loader.loadTexture("assets/textures/dirt.png")));
	m_Registry.emplace<RigidBody2DComponent>(ground, b2_staticBody);
	m_Registry.emplace<BoxCollider2DComponent>(ground, 0.5f, 3, 1, 0.3, 0.5);

	m_Registry.emplace<DistanceJoint2DComponent>(ground2, ground, b2Vec2(0, 0), b2Vec2(0, 0), 0, 6.0f);

	m_Editor.addPlayButtonListener([this]() {
		m_RegistryUtil.store<RigidBody2DComponent, SpriteSheetComponent>(m_Registry);
		PhysicSystem::init(m_Registry, m_World.get());
	});

	m_Editor.addReloadButtonListener([this]() {
		m_RegistryUtil.restore<RigidBody2DComponent, SpriteSheetComponent>(m_Registry);
		m_World = std::make_unique<b2World>(m_Gravity);
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
