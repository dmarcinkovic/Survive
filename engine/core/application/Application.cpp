//
// Created by david on 17. 10. 2021..
//

#include "Application.h"
#include "System.h"
#include "ContactListener.h"
#include "PhysicSystem.h"

Survive::Application::Application(int windowWidth, int windowHeight, const char *title)
		: m_Display(windowWidth, windowHeight, title), m_Light(glm::vec3{100.0f}, glm::vec3{1.0f}),
		  m_Renderer(m_Light), m_Editor(m_Renderer, m_Registry), m_World2D(std::make_unique<b2World>(m_Gravity))
{
	m_Camera.position = glm::vec3{0, 0, 7};

	auto sphere = m_Registry.create();
	m_Registry.emplace<TagComponent>(sphere, "sphere");
	m_Registry.emplace<Transform3DComponent>(sphere, glm::vec3{0, 2, -10}, glm::vec3{1.0f});
	m_Registry.emplace<MaterialComponent>(sphere, false);
	m_Registry.emplace<Render3DComponent>(sphere,
										  TexturedModel(ObjParser::loadObj("assets/models/sphere.obj", m_Loader),
														Texture()));
	m_Registry.emplace<SpriteComponent>(sphere, glm::vec4{0.8f, 0.9f, 0.4f, 1.0f});
	m_Registry.emplace<RigidBody3DComponent>(sphere, rp3d::BodyType::DYNAMIC, 1.0f);
	m_Registry.emplace<SphereCollider3DComponent>(sphere, 1.0f, rp3d::Vector3{0, 0, 0});
	m_Registry.emplace<OutlineComponent>(sphere, false);

	auto sphere2 = m_Registry.create();
	m_Registry.emplace<TagComponent>(sphere2, "sphere2");
	m_Registry.emplace<Transform3DComponent>(sphere2, glm::vec3{1, 4, -10}, glm::vec3{1.0f});
	m_Registry.emplace<MaterialComponent>(sphere2, false);
	m_Registry.emplace<Render3DComponent>(sphere2,
										  TexturedModel(ObjParser::loadObj("assets/models/sphere.obj", m_Loader),
														Texture()));
	m_Registry.emplace<SpriteComponent>(sphere2, glm::vec4{0.8f, 0.3f, 0.1f, 1.0f});
	m_Registry.emplace<RigidBody3DComponent>(sphere2, rp3d::BodyType::DYNAMIC, 1.0f);
	m_Registry.emplace<SphereCollider3DComponent>(sphere2, 1.0f, rp3d::Vector3{0, 0, 0});
	m_Registry.emplace<OutlineComponent>(sphere2, false);

	auto ground = m_Registry.create();
	m_Registry.emplace<TagComponent>(ground, "ground");
	m_Registry.emplace<Transform3DComponent>(ground, glm::vec3{0, -2, -10}, glm::vec3{6, 0.5f, 8});
	m_Registry.emplace<MaterialComponent>(ground, false);
	m_Registry.emplace<Render3DComponent>(ground, TexturedModel(ObjParser::loadObj("assets/models/cube.obj", m_Loader),
																Texture()));
	m_Registry.emplace<SpriteComponent>(ground, glm::vec4{0, 0.3f, 0.8f, 1.0f});
	m_Registry.emplace<RigidBody3DComponent>(ground, rp3d::BodyType::STATIC, 1.0f, false);
	m_Registry.emplace<BoxCollider3DComponent>(ground, rp3d::Vector3{6, 0.5f, 8});
	m_Registry.emplace<OutlineComponent>(ground, false);

	m_ContactListener = std::make_unique<ContactListener>(m_Registry);

	m_Editor.addPlayButtonListener([this]() {
		m_RegistryUtil.store<RigidBody2DComponent, RigidBody3DComponent, SpriteSheetComponent>(m_Registry);
		System::init(m_Registry, m_EventHandler, m_World2D.get(), m_World3D, m_PhysicsCommon);

		m_World2D->SetContactListener(m_ContactListener.get());
	});

	m_Editor.addReloadButtonListener([this]() {
		m_RegistryUtil.restore<RigidBody2DComponent, SpriteSheetComponent, RigidBody3DComponent>(m_Registry);

		m_World2D = std::make_unique<b2World>(m_Gravity);

		m_PhysicsCommon.destroyPhysicsWorld(m_World3D);
		m_World3D = m_PhysicsCommon.createPhysicsWorld();

		System::destroy(m_Registry);
	});

	m_World3D = m_PhysicsCommon.createPhysicsWorld();
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
			System::update(m_Registry, m_World2D.get(), m_World3D);
		}

		m_Display.update();
	}
}
