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
	auto polygon = m_Registry.create();
	m_Registry.emplace<TagComponent>(polygon, "polygon");
	m_Registry.emplace<Transform3DComponent>(polygon, glm::vec3{0, 0.7f, 0}, glm::vec3{0.25f, 0.25f, 1.0f},
											 glm::vec3{0, 0, 30});
	m_Registry.emplace<Render2DComponent>(polygon,
										  TexturedModel(m_Loader.renderQuad(),
														m_Loader.loadTexture("assets/textures/polygon.png")));
	m_Registry.emplace<RigidBody2DComponent>(polygon, b2_dynamicBody);
	m_Registry.emplace<PolygonCollider2DComponent>(polygon,
												   std::vector<b2Vec2>{b2Vec2(-2.5, -0.7), b2Vec2(-0.25, -2.85),
																	   b2Vec2(2.5, -1.5), b2Vec2(1.7, 1.7),
																	   b2Vec2(-1.4, 2)}, 1.0f, 0.3f, 0.5f);

	auto ground = m_Registry.create();
	m_Registry.emplace<TagComponent>(ground, "ground");
	Transform3DComponent groundPos(glm::vec3{-0.55f, -0.8f, 0}, glm::vec3{0.4f, 0.05f, 1.0f});
	m_Registry.emplace<Transform3DComponent>(ground, groundPos);
	m_Registry.emplace<Render2DComponent>(ground,
										  TexturedModel(m_Loader.renderQuad(),
														m_Loader.loadTexture("assets/textures/dirt.png")));
	m_Registry.emplace<RigidBody2DComponent>(ground, b2_staticBody);
	m_Registry.emplace<EdgeCollider2DComponent>(ground, b2Vec2{-4, 0.5}, b2Vec2{4, 0.5}, 1.0f, 0.3, 0.5);

	m_Editor.addPlayButtonListener([this]() {
		PhysicSystem::init(m_Registry, m_World.get());

		m_RegistryUtil.store<RigidBody2DComponent, SpriteSheetComponent>(m_Registry);
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
